; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; KERNEL

;DEFINES PARA EL DIRECTORIO DE PAGINAS DEL KERNEL
%define PDK             0x21000 ;0x21 son los 20 bits mas significativos, a los que luego
                                ;, con paginacion activa, se le agregan 12 bits en 0 para 
                                ;completar la direccion. Los 12 bits menos significativos son
                                ;flags que se cargan en cr3
%define STACK_BASE 0x21000

;SELECTORES DE DESCRIPTORES DE LA GDT
%include "selectores.mac"

BITS 16

;Macros provistas por la catedra para imprimir por pantalla
%include "macrosmodoreal.mac"
%include "macrosmodoprotegido.mac"

%define KORG 0x1200

global start
extern tsss
extern gdt
extern GDT_DESC
extern IDT_DESC
extern inicializar_idt
extern inicializar_dir_kernel
extern inicializar_mmu
extern inicializar_dir_tarea
extern pintar_pantalla
extern inicializar_tsss
extern inicializar_scheduler

extern deshabilitar_pic
extern resetear_pic
extern habilitar_pic

; PUNTO DE ENTRADA DEL KERNEL
start:
		cli ;pues que no me interrumpan por ahora
		jmp bienvenida

		;aca ponemos todos los mensajes
		iniciando: db 'Iniciando el kernel'
		iniciando_len equ $ - iniciando

		modoprotegido: db 'Ahora estamos en modo protegido'
		modoprotegido_len equ $ - modoprotegido 

bienvenida:
		IMPRIMIR_MODO_REAL iniciando, iniciando_len, 0x07, 0, 0

		; habilitar A20
		call habilitar_A20
		; deshabilitar las interrupciones
		cli
		; cargar la GDT
		lgdt [GDT_DESC]
		; setear el bit PE del registro CR0
		mov eax, CR0
		or eax, 1
		mov CR0, eax
		; pasar a modo protegido
		jmp CODIGO_0:.modoProtegido ;esto se hace para cargar CS en el selector 10 (selector de codigo dpl 0)
									;{index: 10 | gdt/ldt = 0 | rpl = 00}
BITS 32
		.modoProtegido: 				;ahora estamos en 32 bits
		; acomodar los segmentos
		xor eax, eax					;eax = 0
		mov ax, DATOS_0					;ax = 11 = selector del segmento de datos nivel 0
		mov ds, ax 					
		;mov es, ax
		;mov gs, ax
		mov ss, ax 						;pila
		mov ax, VIDEO_0 				;el 15avo segmento = video
		mov fs, ax

		
		; seteo la pila
		mov ebp, STACK_BASE
		mov esp, STACK_BASE
		;IMPRIMIR_TEXTO modoprotegido, modoprotegido_len, 0x07, 3, 0
		; pintar pantalla, todos los colores, que bonito!
		mov ebx,0x70FF70FF					;caracter negro, fondo blanco
		mov ecx,1000					;contador de todas las posiciones de la pantalla

		.clear:
			mov [fs:ecx*4-4],ebx
		loop .clear

		mov ebx,0x07FF07FF					;doble caracter blanco, fondo negro
		mov ecx,40
		
		.encabezadoYPie:
			mov [fs:ecx*4-4],ebx
			mov [fs:ecx*4+3836],ebx			;el offset es Columnas*Filas-1*sizeOfCaracter-2
		loop .encabezadoYPie
		; inicializamos la idt
		call inicializar_idt
		lidt [IDT_DESC]

		; Ejercicio 1 - Pregunta 1
		; Imprimo en la fila 26, columna 1 utilizando el segmento de video (para que estalle?)
		;xchg bx,bx
		;mov [fs:26*80*2],bx ;4000 ?
		; inicializamos el directorio y tablas de paginas
		call inicializar_dir_kernel

        ;PAE = 0
        mov eax,cr4
        and eax,0xFFFFFFDF
        mov cr4,eax

        ;Seteamos el CR3 para el kernel
		mov eax,PDK
		mov cr3,eax								;seteo cr3, que apunta al directorio de tablas

		; inicializar el manejador de memoria
        call inicializar_mmu

		; inicializar memoria de tareas
        call pintar_pantalla
        call inicializar_dir_tarea

		; habilitar paginacion
		mov eax,cr0
		or eax,0x80000000
		mov cr0,eax

		; configurar controlador de interrupciones
        call deshabilitar_pic
        call resetear_pic
        call habilitar_pic
        sti

		; inicializar todas las tsss: Son variables Globales, ya estan inicializadas
		; inicializar entradas de la gdt de tss
		; inicializar tarea idle
        call inicializar_tsss

		; inicializar el scheduler
        call inicializar_scheduler

		; cargo la primer tarea null
        mov ax,TAREA_INICIAL    ;indice de la tss de tarea_inicial (indice = 6)
                                ;permisos de supervisor
        ltr ax

		; aca salto a la primer tarea (Idle)
        jmp TAREA_IDLE:0

		jmp $

%include "a20.asm"
