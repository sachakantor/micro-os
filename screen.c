/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/
#include "defines.h"
#include "i386.h"
#include "sched.h"
#include "screen.h"

#define CANT_FILAS_VIDEO 25
#define CANT_COLS_VIDEO 80

#define FILA_SECCION_BLANCA 19
#define FILA_SECCION_GRIS 1

#define FILA_INICIO_ARENA 2
#define FILA_FIN_ARENA 12
#define COL_INICIO_ARENA 2
#define COL_FIN_ARENA 32

#define COL_INICIO_PROBLEMA 41
#define COL_FIN_PROBLEMA 71
#define FILA_INICIO_PROBLEMA 2
#define FILA_FIN_PROBLEMA 15

#define COL_FIN_TURNO_TAREA COL_FIN_ARENA
#define FILA_TURNO_TAREA    FILA_FIN_ARENA+2

//Colores disponibles tanto para bg como fg
#define COLOR_NEGRO 0
#define COLOR_AZUL 1
#define COLOR_VERDE 2
#define COLOR_TURQUESA 3
#define COLOR_ROJO 4
#define COLOR_VIOLETA 5
#define COLOR_MARRON 6
#define COLOR_GRIS  7

//Colores disponibles solo para fg
#define COLOR_GRIS_OSCURO 8
#define COLOR_AZUL_CLARO 9
#define COLOR_VERDE_CLARO 10
#define COLOR_TURQUESA_CLARO 11
#define COLOR_ROJO_CLARO 12
#define COLOR_ROSA 13
#define COLOR_AMARILLO 14
#define COLOR_BLANCO 15


//Definicion de los distintos campos de la pantalla
//BG = background
//FG = foreground
#define COLOR_BG                COLOR_NEGRO
#define COLOR_FG                COLOR_VERDE
#define COLOR_BG_HEADER_FOOT    COLOR_NEGRO
#define COLOR_FG_HEADER_FOOT    COLOR_VERDE
#define COLOR_BG_ARENA          COLOR_GRIS
#define COLOR_FG_ARENA          COLOR_NEGRO
#define COLOR_BG_EXCEP_HEADER   COLOR_NEGRO
#define COLOR_FG_EXCEP_HEADER   COLOR_VERDE_CLARO
#define COLOR_BG_EXCEP          COLOR_NEGRO
#define COLOR_FG_EXCEP          COLOR_VERDE
#define COLOR_BG_TASK_STATUS    COLOR_NEGRO
#define COLOR_FG_TASK_STATUS    COLOR_VERDE
#define COLOR_FG_TASKS          COLOR_NEGRO
#define COLOR_BG_TASK1          COLOR_VERDE
#define COLOR_FG_TASK1          COLOR_FG_TASKS
#define COLOR_BG_TASK2          COLOR_ROJO
#define COLOR_FG_TASK2          COLOR_FG_TASKS
#define COLOR_BG_TASK3          COLOR_TURQUESA
#define COLOR_FG_TASK3          COLOR_FG_TASKS
#define COLOR_BG_TASK4          COLOR_AZUL
#define COLOR_FG_TASK4          COLOR_FG_TASKS
#define COLOR_BG_TASK5          COLOR_VIOLETA
#define COLOR_FG_TASK5          COLOR_FG_TASKS


typedef unsigned short Pixel;

char digito_hexa(unsigned int numero, char n)
{
	unsigned int mascara = 0xF;
	numero >>= (n << 2);
	numero &= mascara;
	if (numero < 10)
		return '0'+numero;
	else
		return 'A'+(numero-10);
}

char obtener_color_fondo(unsigned int fila, unsigned int col)
{
	return (*(Pixel*)(0xB8000 + (fila * CANT_COLS_VIDEO + col) * sizeof(Pixel)) >> 12) & 7;
}

void pintar_pixel(uchar colorFondo, uchar colorCaracter, uchar ascii, unsigned int fila, unsigned int col)
{
	uchar blink = 0, brillante=0;
	Pixel p = (((((((blink << 3) | colorFondo) << 1) | brillante)<<3)|colorCaracter)<<8) | ascii;
	*(Pixel*)(0xB8000 + (fila * CANT_COLS_VIDEO + col) * sizeof(Pixel)) = p;
}

void imprimir_numero_hexa(unsigned int numero, unsigned int fila, unsigned int col)
{
	int i;
	for (i = 7; i >= 0; --i)
		pintar_pixel(COLOR_BG_EXCEP, COLOR_FG_EXCEP, digito_hexa(numero, i),fila, col+7-i);
}

//Variables globales para recordar como estan los relojes de las tareas
unsigned char manillas[4] = {'|','/','-','\\'};
unsigned char manilla_actual_X_tarea[5] = {0,0,0,0,0};

void actualizar_reloj_tareas()
{
    char colorTarea;
    switch (indiceTareaActual)
    {
        case 0:colorTarea=COLOR_BG_TASK1;break;
        case 1:colorTarea=COLOR_BG_TASK2;break;
        case 2:colorTarea=COLOR_BG_TASK3;break;
        case 3:colorTarea=COLOR_BG_TASK4;break;
        case 4:colorTarea=COLOR_BG_TASK5;break;
    }
    manilla_actual_X_tarea[indiceTareaActual] = (manilla_actual_X_tarea[indiceTareaActual]+1)%4;
    pintar_pixel(colorTarea, COLOR_FG_TASKS, manillas[manilla_actual_X_tarea[indiceTareaActual]], FILA_SECCION_BLANCA+indiceTareaActual, 0);
}

//Variable global con los mensajes de la funcion imprimir_turno
char* turno = "Turno de la tarea: ";
char turno_length = 20;
char* nohaytareas = "   Holocausto mundial";
char nohaytareas_length = 21;
void imprimir_turno(){
    unsigned char i,c;
    unsigned char tarea_actual_local = indiceTareaActual;

    for(i=0;i<5;++i){
        tarea_actual_local=(tarea_actual_local+1)%CANT_TAREAS;
        if(tareas[tarea_actual_local] != 0){
            //Imprimimos el mensaje con la tarea que acabamos de ver que es valida
            for(c=0;c<turno_length;++c) //sumpo uno para luego imprmir el numero de tarea
                pintar_pixel(COLOR_BG_HEADER_FOOT, COLOR_FG_HEADER_FOOT, turno[c], FILA_TURNO_TAREA, COL_FIN_TURNO_TAREA-turno_length+1+c);

            pintar_pixel(COLOR_BG_HEADER_FOOT, COLOR_FG_HEADER_FOOT, tarea_actual_local+1+0x30, FILA_TURNO_TAREA, COL_FIN_TURNO_TAREA);
            //sumamos 1 a tarea actual
            //pues es un indice en un array

            break;
        }
    }
    //Si salimos del ciclo porque no hay tareas vivas
    if(i==5){
        //Imprimos el mensaje siamo fori
        for(c=0;c<nohaytareas_length;++c)
            pintar_pixel(COLOR_BG_HEADER_FOOT, COLOR_FG_HEADER_FOOT, nohaytareas[c], FILA_TURNO_TAREA, COL_FIN_TURNO_TAREA-nohaytareas_length+1+c);
    }

}

void pintar_posicion_arena(char caracter, unsigned int indiceArena)
{
	//imprimir_numero_hexa(indiceArena, 0,0);
	char filaArena = indiceArena / 10;
	char colArena = indiceArena % 10;
	char colVideo, filaVideo;
	//Si es el caracter vacio, es la compartida va en el casillero derecho.
	if (caracter == ' ')
	{
		colVideo = COL_INICIO_ARENA+(colArena+1)*3;
		filaVideo = FILA_INICIO_ARENA+filaArena+1;
	}
	else
	{
		colVideo = COL_INICIO_ARENA+(colArena+1)*3-1;
		filaVideo = FILA_INICIO_ARENA+filaArena+1;
	}

	//Pongo en colorTarea el color de fondo asociado a la tarea actual.
	char colorTarea;
	switch (indiceTareaActual)
	{
        case 0:colorTarea=COLOR_BG_TASK1;break;
        case 1:colorTarea=COLOR_BG_TASK2;break;
        case 2:colorTarea=COLOR_BG_TASK3;break;
        case 3:colorTarea=COLOR_BG_TASK4;break;
        case 4:colorTarea=COLOR_BG_TASK5;break;
	}

	if (caracter == 'S')
	{
		//Borro la que tenga mi color de tarea.
		if (obtener_color_fondo(filaVideo,colVideo+1) == colorTarea)
			pintar_pixel(COLOR_BG_ARENA, COLOR_FG_ARENA, ' ', filaVideo, colVideo+1);
    }
	else if (caracter == 'X')
	{
        // No consultamos si el color es el mismo, porque al pedir borrar la pagina
        // de pila o codigo, tarea_inicial ha de coincidir con el owner de la pagina
		pintar_pixel(COLOR_BG_ARENA, COLOR_FG_ARENA, ' ', filaVideo, colVideo);
	}
    else
		pintar_pixel(colorTarea, COLOR_FG_ARENA, caracter, filaVideo, colVideo);
}

void pintar_excepciones(char* mensaje, unsigned int* stack)
{
	//pos  = 00, 01, 02,    03, 04, 05, 06, 07,       08, 09,10,    11, 12,13, 14, 15
	//stack=edi,esi,ebp,esp(v),ebx,edx,ecx,eax,errorcode,eip,cs,eflags,esp,ss,ret,stack0,...
	//Imprimo eax.
	imprimir_numero_hexa(stack[7], FILA_INICIO_PROBLEMA+1, COL_INICIO_PROBLEMA+5);
	//Imprimo ebx.
	imprimir_numero_hexa(stack[4], FILA_INICIO_PROBLEMA+2, COL_INICIO_PROBLEMA+5);
	//Imprimo ecx.
	imprimir_numero_hexa(stack[6], FILA_INICIO_PROBLEMA+3, COL_INICIO_PROBLEMA+5);
	//Imprimo edx.
	imprimir_numero_hexa(stack[5], FILA_INICIO_PROBLEMA+4, COL_INICIO_PROBLEMA+5);
	//Imprimo esi.
	imprimir_numero_hexa(stack[1], FILA_INICIO_PROBLEMA+5, COL_INICIO_PROBLEMA+5);
	//Imprimo edi.
	imprimir_numero_hexa(stack[0], FILA_INICIO_PROBLEMA+6, COL_INICIO_PROBLEMA+5);
	//Imprimo ebp.
	imprimir_numero_hexa(stack[2], FILA_INICIO_PROBLEMA+7, COL_INICIO_PROBLEMA+5);
	//Imprimo esp.
	imprimir_numero_hexa(stack[12], FILA_INICIO_PROBLEMA+8, COL_INICIO_PROBLEMA+5);
	//Imprimo eip.
	imprimir_numero_hexa(stack[9], FILA_INICIO_PROBLEMA+9, COL_INICIO_PROBLEMA+5);
	unsigned int cr0 = rcr0(), cr2=rcr2(),cr3=rcr3(),cr4=rcr4();
	//Imprimo cr0,cr2,cr3,cr4.
	imprimir_numero_hexa(cr0, FILA_INICIO_PROBLEMA+10, COL_INICIO_PROBLEMA+5);
	imprimir_numero_hexa(cr2, FILA_INICIO_PROBLEMA+11, COL_INICIO_PROBLEMA+5);
	imprimir_numero_hexa(cr3, FILA_INICIO_PROBLEMA+12, COL_INICIO_PROBLEMA+5);
	imprimir_numero_hexa(cr4, FILA_INICIO_PROBLEMA+13, COL_INICIO_PROBLEMA+5);
	//Imprimo cs.
	imprimir_numero_hexa(stack[10], FILA_INICIO_PROBLEMA+1, COL_INICIO_PROBLEMA+20);
	//Imprimo ds.
	imprimir_numero_hexa(rds(), FILA_INICIO_PROBLEMA+2, COL_INICIO_PROBLEMA+20);
	//Imprimo es.
	imprimir_numero_hexa(res(), FILA_INICIO_PROBLEMA+3, COL_INICIO_PROBLEMA+20);
	//Imprimo fs.
	imprimir_numero_hexa(rfs(), FILA_INICIO_PROBLEMA+4, COL_INICIO_PROBLEMA+20);
	//Imprimo gs.
	imprimir_numero_hexa(rgs(), FILA_INICIO_PROBLEMA+5, COL_INICIO_PROBLEMA+20);
	//Imprimo ss.
	imprimir_numero_hexa(stack[13], FILA_INICIO_PROBLEMA+6, COL_INICIO_PROBLEMA+20);
	//Imprimo stack.
	unsigned int* stackTarea = (unsigned int*) stack[12];

	int i;
	for (i = 0; i < 5; ++i)
		imprimir_numero_hexa(stackTarea[i], FILA_INICIO_PROBLEMA+8+i,COL_INICIO_PROBLEMA+22);
	//Imprimo eflags.
	imprimir_numero_hexa(stack[11], FILA_FIN_PROBLEMA, COL_INICIO_PROBLEMA+22);
	//Imprimo el nombre de la excepcion.
	for (i = 0; mensaje[i] != 0 && i < 78; ++i)
	{
		if (i < 23)
			pintar_pixel(COLOR_BG_EXCEP_HEADER, COLOR_FG_EXCEP_HEADER, mensaje[i], FILA_INICIO_PROBLEMA, COL_INICIO_PROBLEMA+i);
		pintar_pixel(COLOR_BG_TASK_STATUS, COLOR_FG_TASK_STATUS, mensaje[i], FILA_SECCION_BLANCA+indiceTareaActual, 2+i);
	}
    //Limpio el resto del header por si el nuevo mensaje es mas corto que el mensaje que ya estaba
	while( i < 23)
	{
		pintar_pixel(COLOR_BG_EXCEP_HEADER, COLOR_FG_EXCEP_HEADER, ' ', FILA_INICIO_PROBLEMA, COL_INICIO_PROBLEMA+i);
        ++i;
	}

	char* tarea = "Tarea ";
	//Muestro que tarea fue.
	for (i = 0; i < 6; ++i)
		pintar_pixel(COLOR_BG_EXCEP_HEADER, COLOR_FG_EXCEP_HEADER, tarea[i], FILA_INICIO_PROBLEMA, COL_INICIO_PROBLEMA+24+i);
	pintar_pixel(COLOR_BG_EXCEP_HEADER, COLOR_FG_EXCEP_HEADER, '1'+indiceTareaActual, FILA_INICIO_PROBLEMA, COL_INICIO_PROBLEMA+30);
}

void pintar_pantalla()
{
	uchar c,f;
	//Pinto el header con el nombre del grupo
    char* grupo = "Marley (Sin Huevos)";
	for (c = 0; c < CANT_COLS_VIDEO; ++c)
		pintar_pixel(COLOR_BG_HEADER_FOOT, COLOR_FG_HEADER_FOOT, ' ',0,c);
    for(c = 0; c < 19; ++c)
        pintar_pixel(COLOR_BG_HEADER_FOOT, COLOR_FG_HEADER_FOOT, grupo[c], 0, 0+c);

	//Pinto la parte de gris.
	for (f = FILA_SECCION_GRIS; f < FILA_SECCION_BLANCA; ++f)
		for (c = 0; c < CANT_COLS_VIDEO; ++c)
			pintar_pixel(COLOR_BG, COLOR_FG, ' ',f,c);

	//Pinto los numeros horizontales de la arena.
	for (c = 0; c < 10; ++c)
		pintar_pixel(COLOR_BG, COLOR_FG, '0'+c,FILA_INICIO_ARENA,COL_INICIO_ARENA+(c+1)*3);

	//Pinto los numeros verticales de la arena.
	for (f = 0; f < 10; ++f)
		pintar_pixel(COLOR_BG, COLOR_FG, '0'+f,FILA_INICIO_ARENA+f+1,COL_INICIO_ARENA);

	//Pinto los cuadrados negros de la arena.
	for (f = 0; f < 10; ++f)
	{
		for (c = 0; c < 10; ++c)
		{
			pintar_pixel(COLOR_BG_ARENA, COLOR_FG_ARENA, ' ',FILA_INICIO_ARENA+f+1,COL_INICIO_ARENA+(c+1)*3-1);
			pintar_pixel(COLOR_BG_ARENA, COLOR_FG_ARENA, ' ',FILA_INICIO_ARENA+f+1,COL_INICIO_ARENA+(c+1)*3);
		}
	}

	//Pinto el header del area de problema.
	for (c = COL_INICIO_PROBLEMA; c <= COL_FIN_PROBLEMA; ++c)
		pintar_pixel(COLOR_BG_EXCEP_HEADER, COLOR_FG_EXCEP_HEADER, ' ',FILA_INICIO_PROBLEMA,c);

	//Pinto el area del problema de blanco.
	for (f = FILA_INICIO_PROBLEMA+1; f <= FILA_FIN_PROBLEMA; ++f)
		for (c = COL_INICIO_PROBLEMA; c <= COL_FIN_PROBLEMA; ++c)
			pintar_pixel(COLOR_BG_EXCEP, COLOR_FG_EXCEP, ' ',f,c);

	//Cargo los titulos de los registros de la izquierda.
	char* registros = "EAXEBXECXEDXESIEDIEBPESPEIPCR0CR2CR3CR4";
	for (f = 0; f < 13; ++f)
		for (c = 0; c < 3; ++c)
			pintar_pixel(COLOR_BG_EXCEP, COLOR_FG_EXCEP, registros[f*3+c],FILA_INICIO_PROBLEMA+f+1,COL_INICIO_PROBLEMA+c+1);

	//Cargo los titulos de los registros de la derecha.
	registros = "CSDSESFSGSSS";
	for (f = 0; f < 7; ++f)
		for (c = 0; c < 2; ++c)
			pintar_pixel(COLOR_BG_EXCEP, COLOR_FG_EXCEP, registros[f*2+c],FILA_INICIO_PROBLEMA+f+1,COL_INICIO_PROBLEMA+c+17);

	//Cargo el titulo de stack.
	registros = "stack";
	for (c = 0; c < 5; ++c)
		pintar_pixel(COLOR_BG_EXCEP, COLOR_FG_EXCEP, registros[c],FILA_INICIO_PROBLEMA+7,COL_INICIO_PROBLEMA+c+17);

	//Cargo el titulo de EFLAGS.
	registros = "EFLAGS";
	for (c = 0; c < 6; ++c)
		pintar_pixel(COLOR_BG_EXCEP, COLOR_FG_EXCEP, registros[c],FILA_FIN_PROBLEMA,COL_INICIO_PROBLEMA+c+15);

	//Pinto los headers de las filas blancas.
	pintar_pixel(COLOR_BG_TASK1, COLOR_FG_TASK1, '-',FILA_SECCION_BLANCA,0);
	pintar_pixel(COLOR_BG_TASK1, COLOR_FG_TASK1, '1',FILA_SECCION_BLANCA,1);
	pintar_pixel(COLOR_BG_TASK2, COLOR_FG_TASK2, '\\',FILA_SECCION_BLANCA+1,0);
	pintar_pixel(COLOR_BG_TASK2, COLOR_FG_TASK2, '2',FILA_SECCION_BLANCA+1,1);
	pintar_pixel(COLOR_BG_TASK3, COLOR_FG_TASK3, '|',FILA_SECCION_BLANCA+2,0);
	pintar_pixel(COLOR_BG_TASK3, COLOR_FG_TASK3, '3',FILA_SECCION_BLANCA+2,1);
	pintar_pixel(COLOR_BG_TASK4, COLOR_FG_TASK4, '/',FILA_SECCION_BLANCA+3,0);
	pintar_pixel(COLOR_BG_TASK4, COLOR_FG_TASK4, '4',FILA_SECCION_BLANCA+3,1);
	pintar_pixel(COLOR_BG_TASK5, COLOR_FG_TASK5, '|',FILA_SECCION_BLANCA+4,0);
	pintar_pixel(COLOR_BG_TASK5, COLOR_FG_TASK5, '5',FILA_SECCION_BLANCA+4,1);

	//Pinto la parte de los estados de cada tarea
	for (f = FILA_SECCION_BLANCA; f < CANT_FILAS_VIDEO - 1; ++f)
		for (c = 2; c < CANT_COLS_VIDEO; ++c)
			pintar_pixel(COLOR_BG_TASK_STATUS, COLOR_FG_TASK_STATUS, ' ',f,c);

	//Pinto la ultima fila de negro con letras blancas.
	for (c = 0; c < CANT_COLS_VIDEO; ++c)
		pintar_pixel(COLOR_BG_HEADER_FOOT, COLOR_FG_HEADER_FOOT, ' ', CANT_FILAS_VIDEO-1, c);
}
