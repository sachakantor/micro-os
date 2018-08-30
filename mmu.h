/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#define mascaraPTE 0xFFFFF000
#define PDEtarea 0  /*Primeros 10 bits de 0x003A0000 / 0x003B0000 / 0x003C0000.
                     *Ver estructura del Page Directory Entry
                     *Es el indice del PD de cada tarea que usaremos
                     *(selecciona la direccion del PT de la tarea)
                     */

void inicializar_mmu();
void mapear_pagina(unsigned int virt, unsigned int cr3, unsigned int fisica);
void unmapear_pagina(unsigned int virt, unsigned int cr3);
#endif
