/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "tss.h"
#include "gdt.h"
#include "mmu.h"
#include "i386.h"

extern unsigned short tareas[CANT_TAREAS];
extern unsigned short indiceTareaActual;
extern unsigned char pause;
extern unsigned char step_by_step;

void inicializar_scheduler();
void inicializar_tsss();
unsigned short proximo_indice();
void chuckNorris(char* msj, unsigned int* esp);
void set_page(unsigned int indice_arena);
void get_code_stack();
unsigned char indice_en_la_arena(unsigned int virt);


#endif
