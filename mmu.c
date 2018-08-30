/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/
#include "defines.h"
#include "mmu.h"
#include "i386.h"
#include "screen.h"
#include "paginacion.h"
#include "sched.h"

//Variables globales externas definidas en otros archivos
extern unsigned int pc[];
extern unsigned int ps[];
extern unsigned int px[];

#define uint32 unsigned int
#define PDE_INDEX(virtual) ((uint32) virtual >> 22)
#define PTE_INDEX(virtual) (((uint32) virtual & 0x3FF000) >> 12)
#define ALIGN(dir) (dir & ~0xFFF)
#define PG_PRESENT 0x00000001
#define PG_READ_WRITE 0x00000002
#define PG_USER 0x00000004

void inicializar_mmu() {
}

void inicializar_dir_tarea(){
    //Seteamos los directorios de las tareas
    unsigned short i;
    unsigned short j;
    unsigned char indice;

    for(i=0;i<5;++i){

        //Mapeamos los primeros 2 mb para el kernel y seteamos en present=0 el page dir
        for(j=0;j<TBL_COUNT/2;++j){
            set_tbl_entry(ptt[i],j,1,1,0,0,0,0,0,0,0,j);
            ptt[i][j+TBL_COUNT/2].p=0;
            pdt[i][j].p=0;
            pdt[i][j+TBL_COUNT/2].p=0;
        }

        //Asocio el directorio a su tabla de paginas.
        set_dir_entry(pdt[i],PDEtarea,1,1,1,0,0,0,0,0,(unsigned int)ptt[i]>>12);

        //Mapeo la pagina de codigo. Usameos pdt[], pues las direcciones coinciden con el CR3
        //(i.e: 0x32000 es la direccion fisica del page dir, que coincide con su CR3 pues
        //0x32 es la direccion y 000 son sus atributos)
        mapear_pagina(TASK_CODE, (unsigned int)pdt[i], pc[i]);

        //Mapeo la pagina de pila.
        mapear_pagina(TASK_STACK, (unsigned int)pdt[i], ps[i]);

        //Pinto la las paginas mapeadas en la pantalla
        indiceTareaActual = i; //variable global que se usa para saber el color de la tarea a pintar
        indice = (pc[i] - INIT_LUCHA)/TAMANO_PAGINA;
        pintar_posicion_arena('C',indice);
        indice = (ps[i] - INIT_LUCHA)/TAMANO_PAGINA;
        pintar_posicion_arena('P',indice);


        //Copiamos el codigo de la tarea
        for(j=0;j<TAMANO_PAGINA/4;++j)
            /*Casteamos a int para copiar de a 4 bytes por iteracion */
            ((int*)pc[i])[j] = ts[i][j];
    }
}

void mapear_pagina(unsigned int virt, unsigned int cr3, unsigned int fisica){
    dir_entry* dirPDE = (dir_entry*) (cr3 & mascaraPTE);
    tbl_entry* tblPTE = (tbl_entry*) (dirPDE[PDE_INDEX(virt)].base_tbl<<12);
    tblPTE[PTE_INDEX(virt)].base_pag = fisica>>12;
    tblPTE[PTE_INDEX(virt)].p = 1;
    tblPTE[PTE_INDEX(virt)].rw = 1;
    tblPTE[PTE_INDEX(virt)].us = 1; //QUEREMOS QUE SEA USUARIO
}

void unmapear_pagina(unsigned int virt, unsigned int cr3){
    dir_entry* dirPDE = (dir_entry*) (cr3 & mascaraPTE);
    tbl_entry* tblPTE = (tbl_entry*) (dirPDE[PDE_INDEX(virt)].base_tbl<<12);
    tblPTE[PTE_INDEX(virt)].base_pag = 0;
    tblPTE[PTE_INDEX(virt)].p = 0;
}
