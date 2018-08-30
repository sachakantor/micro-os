/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

#define uchar unsigned char
// pinta toda la pantalla felizmente
char digito_hexa(unsigned int numero, char n);
char obtener_color_fondo(unsigned int fila, unsigned int col);
void pintar_pixel(uchar colorFondo, uchar colorCaracter, uchar ascii, unsigned int fila, unsigned int col);
void imprimir_numero_hexa(unsigned int numero, unsigned int fila, unsigned int col);
void imprimir_turno();
void actualizar_reloj_tareas();
void pintar_posicion_arena(char caracter, unsigned int indiceArena);
void pintar_excepciones(char* mensaje, unsigned int* stack);
void pintar_pantalla();

#endif
