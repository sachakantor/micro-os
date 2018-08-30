/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/
#include "defines.h"
#include "tss.h"
//#include "gdt.h"


tss tsss[TAM_TSSS] = { /*considero las 5 tareas +tarea_inicial+tarea_idle*/
    //TSS de la tarea 1
    (tss) {
        (unsigned short) 0,         //ptl
        (unsigned short) 0,         //unused0
        (unsigned int) STT1,		//esp0
        (unsigned short) DATOS_0,   //ss0
        (unsigned short) 0,         //unused1
        (unsigned int) 0,           //esp1
        (unsigned short) 0,         //ss1
        (unsigned short) 0,         //unused2
        (unsigned int) 0,           //esp2
        (unsigned short) 0,         //ss2
        (unsigned short) 0,         //unused3
        (unsigned int) PDT1,        //cr3 Es 0x30000, los 000 son los atributos y 0x30 la direccion
        (unsigned int) TASK_CODE,   //eip
        (unsigned int) 0x202,       //eflags
        (unsigned int) 0,           //eax
        (unsigned int) 0,           //ecx
        (unsigned int) 0,           //edx
        (unsigned int) 0,           //ebx
        (unsigned int) TASK_STACK+0x1000,  //esp
        (unsigned int) TASK_STACK+0x1000,  //ebp
        (unsigned int) 0,           //esi
        (unsigned int) 0,           //edi
        (unsigned short) DATOS_3,   //es
        (unsigned short) 0,         //unused4
        (unsigned short) CODIGO_3,  //cs
        (unsigned short) 0,         //unused5
        (unsigned short) DATOS_3,   //ss
        (unsigned short) 0,         //unused6
        (unsigned short) DATOS_3,   //ds
        (unsigned short) 0,         //unused7
        (unsigned short) DATOS_3,   //fs
        (unsigned short) 0,         //unused8
        (unsigned short) DATOS_3,   //gs
        (unsigned short) 0,         //unused9
        (unsigned short) 0,         //ldt
        (unsigned short) 0,         //unused10
        (unsigned short) 0,         //dtrap
        (unsigned short) 0xFFFF     //iomap
    },

    //TSS de la tarea 2
    (tss) {
        (unsigned short) 0,         //ptl
        (unsigned short) 0,         //unused0
        (unsigned int) STT2,        //esp0
        (unsigned short) DATOS_0,   //ss0
        (unsigned short) 0,         //unused1
        (unsigned int) 0,           //esp1
        (unsigned short) 0,         //ss1
        (unsigned short) 0,         //unused2
        (unsigned int) 0,           //esp2
        (unsigned short) 0,         //ss2
        (unsigned short) 0,         //unused3
        (unsigned int) PDT2,        //cr3 Es 0x31000, los 000 son los atributos y 0x31 la direccion
        (unsigned int) TASK_CODE,   //eip
        (unsigned int) 0x202,       //eflags
        (unsigned int) 0,           //eax
        (unsigned int) 0,           //ecx
        (unsigned int) 0,           //edx
        (unsigned int) 0,           //ebx
        (unsigned int) TASK_STACK+0x1000,  //esp
        (unsigned int) TASK_STACK+0x1000,  //ebp
        (unsigned int) 0,           //esi
        (unsigned int) 0,           //edi
        (unsigned short) DATOS_3,   //es
        (unsigned short) 0,         //unused4
        (unsigned short) CODIGO_3,  //cs
        (unsigned short) 0,         //unused5
        (unsigned short) DATOS_3,   //ss
        (unsigned short) 0,         //unused6
        (unsigned short) DATOS_3,   //ds
        (unsigned short) 0,         //unused7
        (unsigned short) DATOS_3,   //fs
        (unsigned short) 0,         //unused8
        (unsigned short) DATOS_3,   //gs
        (unsigned short) 0,         //unused9
        (unsigned short) 0,         //ldt
        (unsigned short) 0,         //unused10
        (unsigned short) 0,         //dtrap
        (unsigned short) 0xFFFF     //iomap
    },

    //TSS de la tarea 3
    (tss) {
        (unsigned short) 0,         //ptl
        (unsigned short) 0,         //unused0
        (unsigned int) STT3,        //esp0
        (unsigned short) DATOS_0,   //ss0
        (unsigned short) 0,         //unused1
        (unsigned int) 0,           //esp1
        (unsigned short) 0,         //ss1
        (unsigned short) 0,         //unused2
        (unsigned int) 0,           //esp2
        (unsigned short) 0,         //ss2
        (unsigned short) 0,         //unused3
        (unsigned int) PDT3,        //cr3 Es 0x32000, los 000 son los atributos y 0x32 la direccion
        (unsigned int) TASK_CODE,   //eip
        (unsigned int) 0x202,       //eflags
        (unsigned int) 0,           //eax
        (unsigned int) 0,           //ecx
        (unsigned int) 0,           //edx
        (unsigned int) 0,           //ebx
        (unsigned int) TASK_STACK+0x1000,  //esp
        (unsigned int) TASK_STACK+0x1000,  //ebp
        (unsigned int) 0,           //esi
        (unsigned int) 0,           //edi
        (unsigned short) DATOS_3,   //es
        (unsigned short) 0,         //unused4
        (unsigned short) CODIGO_3,  //cs
        (unsigned short) 0,         //unused5
        (unsigned short) DATOS_3,   //ss
        (unsigned short) 0,         //unused6
        (unsigned short) DATOS_3,   //ds
        (unsigned short) 0,         //unused7
        (unsigned short) DATOS_3,   //fs
        (unsigned short) 0,         //unused8
        (unsigned short) DATOS_3,   //gs
        (unsigned short) 0,         //unused9
        (unsigned short) 0,         //ldt
        (unsigned short) 0,         //unused10
        (unsigned short) 0,         //dtrap
        (unsigned short) 0xFFFF     //iomap
    },

    //TSS de la tarea 4
    (tss) {
        (unsigned short) 0,         //ptl
        (unsigned short) 0,         //unused0
        (unsigned int) STT4,        //esp0
        (unsigned short) DATOS_0,   //ss0
        (unsigned short) 0,         //unused1
        (unsigned int) 0,           //esp1
        (unsigned short) 0,         //ss1
        (unsigned short) 0,         //unused2
        (unsigned int) 0,           //esp2
        (unsigned short) 0,         //ss2
        (unsigned short) 0,         //unused3
        (unsigned int) PDT4,        //cr3 Es 0x33000, los 000 son los atributos y 0x33 la direccion
        (unsigned int) TASK_CODE,   //eip
        (unsigned int) 0x202,       //eflags
        (unsigned int) 0,           //eax
        (unsigned int) 0,           //ecx
        (unsigned int) 0,           //edx
        (unsigned int) 0,           //ebx
        (unsigned int) TASK_STACK+0x1000,  //esp
        (unsigned int) TASK_STACK+0x1000,  //ebp
        (unsigned int) 0,           //esi
        (unsigned int) 0,           //edi
        (unsigned short) DATOS_3,   //es
        (unsigned short) 0,         //unused4
        (unsigned short) CODIGO_3,  //cs
        (unsigned short) 0,         //unused5
        (unsigned short) DATOS_3,   //ss
        (unsigned short) 0,         //unused6
        (unsigned short) DATOS_3,   //ds
        (unsigned short) 0,         //unused7
        (unsigned short) DATOS_3,   //fs
        (unsigned short) 0,         //unused8
        (unsigned short) DATOS_3,   //gs
        (unsigned short) 0,         //unused9
        (unsigned short) 0,         //ldt
        (unsigned short) 0,         //unused10
        (unsigned short) 0,         //dtrap
        (unsigned short) 0xFFFF     //iomap
    },

    //TSS de la tarea 5
    (tss) {
        (unsigned short) 0,         //ptl
        (unsigned short) 0,         //unused0
        (unsigned int) STT5,        //esp0
        (unsigned short) DATOS_0,   //ss0
        (unsigned short) 0,         //unused1
        (unsigned int) 0,           //esp1
        (unsigned short) 0,         //ss1
        (unsigned short) 0,         //unused2
        (unsigned int) 0,           //esp2
        (unsigned short) 0,         //ss2
        (unsigned short) 0,         //unused3
        (unsigned int) PDT5,        //cr3 Es 0x34000, los 000 son los atributos y 0x34 la direccion
        (unsigned int) TASK_CODE,   //eip
        (unsigned int) 0x202,       //eflags
        (unsigned int) 0,           //eax
        (unsigned int) 0,           //ecx
        (unsigned int) 0,           //edx
        (unsigned int) 0,           //ebx
        (unsigned int) TASK_STACK+0x1000,  //esp
        (unsigned int) TASK_STACK+0x1000,  //ebp
        (unsigned int) 0,           //esi
        (unsigned int) 0,           //edi
        (unsigned short) DATOS_3,   //es
        (unsigned short) 0,         //unused4
        (unsigned short) CODIGO_3,  //cs
        (unsigned short) 0,         //unused5
        (unsigned short) DATOS_3,   //ss
        (unsigned short) 0,         //unused6
        (unsigned short) DATOS_3,   //ds
        (unsigned short) 0,         //unused7
        (unsigned short) DATOS_3,   //fs
        (unsigned short) 0,         //unused8
        (unsigned short) DATOS_3,   //gs
        (unsigned short) 0,         //unused9
        (unsigned short) 0,         //ldt
        (unsigned short) 0,         //unused10
        (unsigned short) 0,         //dtrap
        (unsigned short) 0xFFFF     //iomap
    },

    (tss) {},  /*tarea_inicial - Indice = 5
                *No es necesaria setearla pues aquí se guardara el contexto inicial
                *Al que nunca se volvera, ademas. Solo se necesita el espacio en memoria
                */

    //TSS de la tarea idle - Indice = 6
    (tss) {
        (unsigned short) 0,         //ptl
        (unsigned short) 0,         //unused0
        (unsigned int) 0,           //esp0 No es necesario ya que idle corre como supervisor,
        (unsigned short) 0,         //ss0 entonces cuando hay una interrupcion no hay cambio de privilegios
        (unsigned short) 0,         //unused1
        (unsigned int) 0,           //esp1
        (unsigned short) 0,         //ss1
        (unsigned short) 0,         //unused2
        (unsigned int) 0,           //esp2
        (unsigned short) 0,         //ss2
        (unsigned short) 0,         //unused3
        (unsigned int) PDK,         //cr3 Es 0x21000, los 000 son los atributos y 0x21 la direccion
        (unsigned int) TASK_CODE,   //eip
        (unsigned int) 0x202,       //eflags
        (unsigned int) 0,           //eax
        (unsigned int) 0,           //ecx
        (unsigned int) 0,           //edx
        (unsigned int) 0,           //ebx
        (unsigned int) STTI,		//esp
        (unsigned int) STTI,		//ebp
        (unsigned int) 0,           //esi
        (unsigned int) 0,           //edi
        (unsigned short) DATOS_0,   //es
        (unsigned short) 0,         //unused4
        (unsigned short) CODIGO_0,  //cs
        (unsigned short) 0,         //unused5
        (unsigned short) DATOS_0,   //ss
        (unsigned short) 0,         //unused6
        (unsigned short) DATOS_0,   //ds
        (unsigned short) 0,         //unused7
        (unsigned short) VIDEO_0,   //fs
        (unsigned short) 0,         //unused8
        (unsigned short) DATOS_0,   //gs
        (unsigned short) 0,         //unused9
        (unsigned short) 0,         //ldt
        (unsigned short) 0,         //unused10
        (unsigned short) 0,         //dtrap
        (unsigned short) 0xFFFF     //iomap
    }

};