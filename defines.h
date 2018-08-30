/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definiciones globales del sistema
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* TAREAS */
#define CANT_TAREAS   5
#define TAM_TSSS      CANT_TAREAS+2 /*Considero la tarea_inicial y tarea_idle*/

#define  TASK_CODE    0x3A0000 /* direccion virtual codigo */
#define  TASK_STACK   0x3B0000 /* direccion virtual stack  */
#define  TASK_SHARE   0x3C0000 /* direccion virtual share  */

/* MEMORIA */
#define TAMANO_PAGINA 0x1000
#define VIDEO         0xB8000

#define BOOTSECTOR    0x01000 /* direccion fisica de comienzo del bootsector (copiado) */
#define KERNEL        0x01200 /* direccion fisica de comienzo del kernel */

#define  TASKIDLE     0x10000 /* direccion fisica del codigo de la tarea idle */
#define  TASK1        0x11000 /* direccion fisica del codigo de la tarea tarea 1 */
#define  TASK2        0x12000 /* direccion fisica del codigo de la tarea tarea 2 */
#define  TASK3        0x13000 /* direccion fisica del codigo de la tarea tarea 3 */
#define  TASK4        0x14000 /* direccion fisica del codigo de la tarea tarea 4 */
#define  TASK5        0x15000 /* direccion fisica del codigo de la tarea tarea 5 */
//Subi el STK en 0x1000 para que apunte al fondo de la pila y no al tope
#define  STK          0x21000 /* direccion fisica para el stack del kernel */
#define  PDK          0x21000 /* direccion fisica para el directorio de paginas */
#define  PTK          0x22000 /* direccion fisica para la tabla de paginas */


#define  PDT1         0x30000 /* direccion fisica para el directorio de paginas de la tarea 1 */
#define  PDT2         0x31000 /* direccion fisica para el directorio de paginas de la tarea 2 */
#define  PDT3         0x32000 /* direccion fisica para el directorio de paginas de la tarea 3 */
#define  PDT4         0x33000 /* direccion fisica para el directorio de paginas de la tarea 4 */
#define  PDT5         0x34000 /* direccion fisica para el directorio de paginas de la tarea 5 */


#define  PTT1         0x35000 /* direccion fisica para la tabla de paginas de la tarea 1 */
#define  PTT2         0x36000 /* direccion fisica para la tabla de paginas de la tarea 2 */
#define  PTT3         0x37000 /* direccion fisica para la tabla de paginas de la tarea 3 */
#define  PTT4         0x38000 /* direccion fisica para la tabla de paginas de la tarea 4 */
#define  PTT5         0x39000 /* direccion fisica para la tabla de paginas de la tarea 5 */
//Subi todos estos defines en 0x1000 para que apunten al fondo de la pila y no al tope
#define  STT1         0x3B000 /* direccion fisica para la pila de nivel 0 de la tarea 1 */
#define  STT2         0x3C000 /* direccion fisica para la pila de nivel 0 de la tarea 2 */
#define  STT3         0x3D000 /* direccion fisica para la pila de nivel 0 de la tarea 3 */
#define  STT4         0x3E000 /* direccion fisica para la pila de nivel 0 de la tarea 4 */
#define  STT5         0x3F000 /* direccion fisica para la pila de nivel 0 de la tarea 5 */
#define  STTI         0x40000 /* direccion fisica para la pila de la tarea idle */

/* AREA DE LUCHA */
#define  INIT_LUCHA 0x100000         /* direccion de comienzo del espacio de lucha */
#define  END_LUCHA  0x100000+100-1   /* direccion de final del espacio de lucha */

/* ATRIBUTOS PAGINAS */
#define UNO 0x00000001
#define RW  0x00000002
#define US  0x00000004

/* INDICES DE SEGMENTOS */
#define CODIGO_0 0x0050
#define DATOS_0  0x0058
#define CODIGO_3 0x0063
#define DATOS_3  0x006B
#define VIDEO_0  0x0070


/* SELECTORES DE DESCRIPTORES DE LA GDT */
#define TAREA_1         0xB  //indice 1 con permisos de usuario
#define TAREA_2         0x13 //indice 2 con permisos de usuario
#define TAREA_3         0x1B //indice 3 con permisos de usuario
#define TAREA_4         0x23 //indice 4 con permisos de usuario
#define TAREA_5         0x2B //indice 5 con permisos de usuario
#define TAREA_INICIAL   0x30 //indice 6 con permisos de supervisor
#define TAREA_IDLE      0x38 //indice 7 con permisos de supervisor

#endif
