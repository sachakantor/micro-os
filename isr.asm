; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

global reloj
global teclado
global serviciosOS
global indiceArenaNoValido

BITS 32

%include "macrosmodoprotegido.mac"
%include "selectores.mac"

%define SET_PAGE         286
%define GET_CODE_STACK   386
%define TASK_SHARE   0x3C0000 ;direccion virtual share

extern fin_intr_pic1
extern set_page
extern get_code_stack
extern proximo_indice
extern chuckNorris
extern pintar_excepciones
extern pintar_posicion_arena
extern indice_en_la_arena
extern actualizar_reloj_tareas
extern imprimir_turno
extern pause
extern step_by_step

offset: dd 0
selector: dw 0

%include "mensajesInt.mac"

; Mensajes
;	Parametros:
;			%1		Numero de Interrupcion
%macro ISR 1
	global _isr%1
	_isr%1:
    cli
    pushad
    ;IMPRIMIR_TEXTO int%1, int%1_len, 0x07, 0, 0
    push esp
    push int%1
    call chuckNorris
    call fin_intr_pic1
    jmp TAREA_IDLE:0              ;voy al idle por el resto del quantum, y nunca mas la veremos again
    popad
    sti
    iret
%endmacro

;Con un loop de nasm, definimos las rutinas de atencion de 
;interrupciones desde la 0 a la 19. Utilizo la macro ISR
%assign i 0
%rep 20
    ISR i
    %assign i i+1
%endrep

; rutina de TECLADO
aleatorio: db '0x0F'
teclado:
	cli
	pushad
	call fin_intr_pic1
    in al, 0x60             ;leo el puerto
    cmp al,0x99             ;makecode 'p'+0x80 (breakcode de 'p')
    jne .noEsP
    mov byte [pause],0x1        ;seteo la variable global 'pause" en 1
    jmp .fin
.noEsP:
        cmp al,0x93             ;makecode 'r'+0x80 (breakcode de 'r')
        jne .noEsPNiR
        mov byte [pause],0x0    ;seteo la variable global 'pause' en 0
        jmp .fin
.noEsPNiR:
        cmp al,0x9F             ;makecode 's'+0x80 (breakcode de 's')
        jne .niS
        mov byte [step_by_step],0x1
        jmp .fin
    ;Codigo Ejercicio 3
    .niS:
        ;Chequeo si es un numero
        cmp al,0x02             ;0x02 = makecode de 1
        jl .fin                 ;no es un numero
        cmp al,0x0b             ;0x0b = makecode de 0
        jg .fin                 ;no es un numero
        jl .noEsCero

        ;si es cero, es un garron
        sub al, 0xA 			;lo reemplazo de manera que
                                ;al sumarle 0x2f quede '0'
    .noEsCero:
        ;Procesamos el numero
        add al,0x2F             ;lo convierto a su codigo ASCII
        add [aleatorio],al
        mov ah,[aleatorio]
        or ah, 0x0F 			;blanco brillante
        and ah, 0x7F 			;no titiles
        mov word [fs:79*2], ax 	;arriba a la derecha

    .fin:
	    popad
    	sti

	iret

; rutina de SERVICIOS
serviciosOS:
    ;Codigo del ejercicio 3
	;cli
	;pushad
	;call fin_intr_pic1
	;mov eax, 42
	;popad
	;sti
	;iret

    ;Codigo del ejercicio 7
    cli
    pushad
    .get_code_stack:
        cmp eax,GET_CODE_STACK
        jne .set_page
        popad
        call get_code_stack
        jmp .finGetCodeStack    ;es particular, ya que devuelve datos por registro
    .set_page:
        cmp eax,SET_PAGE
        jne .desalojar
        push ebx
        call set_page
        jmp TAREA_IDLE:0        ;voy al idle por el resto del quantum
        add esp,4               ;por el push ebx de .set_page
        jmp .fin
    .desalojar:
        push esp
        push int69
        call chuckNorris
        call fin_intr_pic1
        jmp TAREA_IDLE:0              ;voy al idle por el resto del quantum, y nunca mas la veremos again
    .fin:
    popad
    .finGetCodeStack:
    sti
    iret

; rutina llamada cuando se pide mapear un indice no valido
indiceArenaNoValido:
    cli
    pushad
    push esp
    push int70
    call chuckNorris
    call fin_intr_pic1
    jmp TAREA_IDLE:0              ;voy al idle por el resto del quantum, y nunca mas la veremos again
    popad
    sti
    iret

; rutina del reloj
reloj:
    ;Codigo Ejercicio 5
	;cli
	;pushad
	;call proximo_reloj	
	;popad
	;sti
	;iret
    
    ;Codigo Ejercicio 7
    cli
    pushad
    call proximo_reloj
    call imprimir_turno
    call proximo_indice         ;ax = selector de la ste tarea
                                ;Va a ser TAREA_IDLE 
                                ;en caso de no haber mas tareas
                                ;vivas o en caso de haber presionado
                                ;pause

    ;Verificamos que no vayamos a saltar a la tarea
    ;que se esta ejecutando, ya que si eso llegase a 
    ;ocurrir, habría una excepcion porque la tss
    ;va a estar marcada como busy (esto puede ocurrir
    ;por ejemplo, si queda una sola tarea viva y la misma
    ;no pide una pagina compartida)
    str bx                      ; bx = tr
    cmp bx,ax
    je .continuarConLaTarea

    ;Si hay que saltar a una tarea
    mov [selector], ax
    call actualizar_reloj_tareas
    call fin_intr_pic1
    jmp far [offset] 				;no se puede hacer jmp far a registro
    jmp .end
        
    .continuarConLaTarea:
        ;Vemos si continuamos con una tarea distinto que IDLE para
        ;seguir actualizando su reloj
        cmp bx,TAREA_IDLE
        je .esIDLE
        call actualizar_reloj_tareas    ;para que el reloj de la tarea
                                        ;siga girando en caso de no
                                        ;haber un cambio de tarea
        .esIDLE:
        call fin_intr_pic1
    
    .end:
    popad
    sti
    iret

proximo_reloj:
	pushad
	inc DWORD [isrnumero]
	mov ebx, [isrnumero]
	cmp ebx, 0x4
	jl .ok
		mov DWORD [isrnumero], 0x0
		mov ebx, 0
	.ok:
		add ebx, isrClock
		IMPRIMIR_TEXTO ebx, 1, 0x0f, 24, 79
	popad
	ret
	
isrnumero: dd 0x00000000
isrClock:  db '|/-\'
