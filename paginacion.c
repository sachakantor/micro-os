/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion del directorio/tablas de paginas
*/

#include "defines.h"
#include "paginacion.h"
//#include "tss.h"
#include "mmu.h"

void set_dir_entry(dir_entry* const dir, unsigned short indice,
                        unsigned char p,
                        unsigned char rw,
                        unsigned char us,
                        unsigned char pwt,
                        unsigned char pcd,
                        unsigned char a,
                        unsigned char ps,
                        unsigned char g,
                        unsigned int base_tbl
                    ) {
    dir[indice].p = p;
    dir[indice].rw = rw;
    dir[indice].us = us;
    dir[indice].pwt = pwt;
    dir[indice].pcd = pcd;
    dir[indice].a = a;
    dir[indice].zero = (unsigned char) 0;
    dir[indice].ps = ps;
    dir[indice].g = g;
    dir[indice].disponible = (unsigned char) 0;
    dir[indice].base_tbl = base_tbl;
}

void set_tbl_entry(tbl_entry* const tbl, unsigned short indice,
                        unsigned char p,
                        unsigned char rw,
                        unsigned char us,
                        unsigned char pwt,
                        unsigned char pcd,
                        unsigned char a,
                        unsigned char d,
                        unsigned char pat,
                        unsigned char g,
                        unsigned int base_pag
                    ) {
    tbl[indice].p = p;
    tbl[indice].rw = rw;
    tbl[indice].us = us;
    tbl[indice].pwt = pwt;
    tbl[indice].pcd = pcd;
    tbl[indice].a = a;
    tbl[indice].d = d;
    tbl[indice].pat = pat;
    tbl[indice].g = g;
    tbl[indice].disponible = (unsigned char) 0;
    tbl[indice].base_pag = base_pag;
}

//Arrays globales que facilitan la iteracion sobre las direcciones relacionadas con las tareas
//Las definimos de formas global ya que son utiles para mas de un archivo de codigo
dir_entry* pdt[] = {(dir_entry*)PDT1,(dir_entry*)PDT2,(dir_entry*)PDT3,(dir_entry*)PDT4,(dir_entry*)PDT5};
tbl_entry* ptt[] = {(tbl_entry*)PTT1,(tbl_entry*)PTT2,(tbl_entry*)PTT3,(tbl_entry*)PTT4,(tbl_entry*)PTT5};
int* ts[] = {(int*)TASK1,(int*)TASK2,(int*)TASK3,(int*)TASK4,(int*)TASK5};

//Funciones
void inicializar_dir_kernel() {
    unsigned short i;
    //Entrada del PD del kernel. 
	set_dir_entry((dir_entry*) PDK,0,1,1,0,0,0,0,0,0,PTK >> 12);
    //Resto de las entradas en 0
    for(i=1;i<DIR_COUNT;++i){
		set_dir_entry((dir_entry*) PDK,i,0,1,0,0,0,0,0,0,0);
    }
//	set_dir_entry((dir_entry*) PDK,1,1,1,0,0,0,0,0,0,PTK >> 12);
    //Identity Mapping para la primer mitad
    for(i=0;i<TBL_COUNT/2;++i){
        set_tbl_entry((tbl_entry*) PTK,i,1,1,0,0,0,0,0,0,0,(unsigned int) i);
        set_tbl_entry((tbl_entry*) PTK,i+TBL_COUNT/2,0,1,0,0,0,0,0,0,0,0);
    }
    //set_tbl_entry((tbl_entry*) PTK,(TBL_COUNT/2) -1,1,1,1,0,0,0,0,0,0,(unsigned int)(TBL_COUNT/2) -2);
    //Mapeo la direccion virtual del codigo de la IDLE
  
    mapear_pagina(TASK_CODE,PDK,TASKIDLE);
};
