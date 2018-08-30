/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/
#include "defines.h"
#include "screen.h"
#include "i386.h"

#include "sched.h"
#include "mmu.h"
#include "paginacion.h"
#include "gdt.h"

#define uint32 unsigned int
#define PDE_INDEX(virtual) ((uint32) virtual >> 22)
#define PTE_INDEX(virtual) (((uint32) virtual & 0x3FF000) >> 12)

unsigned short tareas[CANT_TAREAS];
unsigned short indiceTareaActual;
unsigned char pause;
unsigned char step_by_step;

void inicializar_scheduler() {
    unsigned char i;
    //unsigned char indice;
    for(i=0;i<CANT_TAREAS;++i){
        tareas[i] = ((i+1)<<3)+3; /*esto se debe a como llenamos la gdt
                                   *dando privilegios de usuarios
                                   *a los selectores de los descriptores
                                   *de las tareas.
                                   */

        indiceTareaActual = 4;
    pause = 1;
    step_by_step = 0;
    }
}

void inicializar_tsss() {
    unsigned char i;
    for(i=0;i<TAM_TSSS;++i){ //Asumimos que cant_tareas es menor o igual a 10
        gdt[i+1].base_0_15 = (unsigned int)&tsss[i];
        gdt[i+1].base_23_16 = (unsigned int)&tsss[i]>>16;
        gdt[i+1].base_31_24 = (unsigned int)&tsss[i]>>24;
    }
}

unsigned short proximo_indice() {
   /* unsigned char res = TAREA_IDLE;
    if(pause == 0 || step_by_step != 0){
        unsigned char i = (indiceTareaActual+1) % CANT_TAREAS;
        while (tareas[i] == 0 && i!= indiceTareaActual){
          i = (i + 1) % CANT_TAREAS;
        }
        indiceTareaActual = i;
        res = tareas[i];
        if(step_by_step != 0)
            step_by_step = 0;
    }
    return res;*/
    unsigned short proximo_indice_gdt = TAREA_IDLE;

    if(pause == 0 || step_by_step != 0) {
        unsigned char i;
        for(i=0;i<5;++i){
            indiceTareaActual=(indiceTareaActual+1)%CANT_TAREAS;
            if(tareas[indiceTareaActual] != 0){
                proximo_indice_gdt = tareas[indiceTareaActual];
                break;
            }
        }
        if(step_by_step != 0)
            step_by_step = 0;
    }

    return proximo_indice_gdt;  //TAREA_IDLE significa que no quedan tareas por ejecutar
                              //o que estamos en pausa
}

void chuckNorris(char* msj, unsigned int* esp){
    unsigned char i;
    tareas[indiceTareaActual] = 0x0;
    //Pintamos la pantalla con los datos pertinentes
    pintar_excepciones(msj,esp);

    i = indice_en_la_arena(TASK_CODE);
    pintar_posicion_arena('X',i);

    i = indice_en_la_arena(TASK_STACK);
    pintar_posicion_arena('X',i);

    i = indice_en_la_arena(TASK_SHARE);
    if (i<100) pintar_posicion_arena('S',i);
}

/*En lugar de pasarle parametros por la pila, como dice la convencion, se lo
 * pasamos por registro.
 *
 * ebx = indice de la pagina a mapear
 */
void set_page(unsigned int indice_arena){
    //unsigned int indice_arena = rebx(); //Este es el indice en la arena, luego lo convertiremos a la dir fisica
    if(indice_arena < 0 || indice_arena > 99)
        __asm __volatile("int $70");
    else {
        //Si ya tenia una pagina compartida, la borramos del mapa de la arena
        unsigned char indice_pag_vieja = indice_en_la_arena(TASK_SHARE);
        if(indice_pag_vieja != 100)
            pintar_posicion_arena('S',indice_pag_vieja);

        unsigned int dir_fisica = indice_arena*TAMANO_PAGINA+INIT_LUCHA;
        mapear_pagina(TASK_SHARE,rcr3(),dir_fisica);
        pintar_posicion_arena(' ',indice_arena);
    }
}

/*No devolvemos el resultado por pila, sino por registros
 * La convencion, bien gracias!
 *
 * ecx = devolvemos el indice de la pagina de codigo
 * edx = devolvemos el indice de la pagina de pila
 */
void get_code_stack(){
    dir_entry* dir = (dir_entry*) (rcr3() & mascaraPTE);
    tbl_entry* tbl = (tbl_entry*) (dir[PDE_INDEX(TASK_CODE)].base_tbl<<12);
    unsigned int dir_fisica = tbl[PTE_INDEX(TASK_CODE)].base_pag << 12;
    lecx((dir_fisica-INIT_LUCHA)/TAMANO_PAGINA);

    tbl = (tbl_entry*) (dir[PDE_INDEX(TASK_STACK)].base_tbl<<12);
    dir_fisica = tbl[PTE_INDEX(TASK_STACK)].base_pag << 12;
    ledx((dir_fisica-INIT_LUCHA)/TAMANO_PAGINA);
}

unsigned char indice_en_la_arena(unsigned int virt){
    unsigned int result;
    dir_entry* dir = (dir_entry*) (rcr3() & mascaraPTE);
    tbl_entry* tbl = (tbl_entry*) (dir[PDE_INDEX(virt)].base_tbl<<12);

    if(tbl[PTE_INDEX(virt)].p)
        result = (((tbl[PTE_INDEX(virt)].base_pag << 12)-INIT_LUCHA)/TAMANO_PAGINA);
    else
        result = 100;

    return result;
}
