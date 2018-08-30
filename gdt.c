/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/
#include "defines.h"
#include "gdt.h"

gdt_entry gdt[GDT_COUNT] = {
	/* Descriptor nulo*/
	(gdt_entry){(unsigned int) 0x00000000, (unsigned int) 0x00000000 },

  /* TSS Tarea 1 - Indice = 1 */
    (gdt_entry){
      (unsigned short) 103,//limite
      (unsigned short) 0,//base
      (unsigned char) 0,//base
      (unsigned char) 9,//Type
      (unsigned char) 0,//Fijo
      (unsigned char) 3,//Nivel 3 
      (unsigned char) 1,//Presente
      (unsigned char) 0,//limite
      (unsigned char) 1,//AVL DUDA!!
      (unsigned char) 0,//FIJO
      (unsigned char) 0,//FIJO
      (unsigned char) 0,//granularity 1b 
      (unsigned char) 0 //base
    },
/* TSS Tarea 2 - Indice = 2 */
    (gdt_entry){
      (unsigned short) 103,//limite
      (unsigned short) 0,//base
      (unsigned char) 0,//base
      (unsigned char) 9,//Type
      (unsigned char) 0,//Fijo
      (unsigned char) 3,//Nivel 3 
      (unsigned char) 1,//Presente
      (unsigned char) 0,//limite
      (unsigned char) 1,//AVL DUDA!!
      (unsigned char) 0,//FIJO
      (unsigned char) 0,//FIJO
      (unsigned char) 0,//granularity 1b 
      (unsigned char) 0 //base
    },
/* TSS Tarea 3 - Indice = 3 */
    (gdt_entry){
      (unsigned short) 103,//limite
      (unsigned short) 0,//base
      (unsigned char) 0,//base
      (unsigned char) 9,//Type
      (unsigned char) 0,//Fijo
      (unsigned char) 3,//Nivel 3 
      (unsigned char) 1,//Presente
      (unsigned char) 0,//limite
      (unsigned char) 1,//AVL DUDA!!
      (unsigned char) 0,//FIJO
      (unsigned char) 0,//FIJO
      (unsigned char) 0,//granularity 1b 
      (unsigned char) 0 //base
    },
/* TSS Tarea 4 - Indice = 4 */
    (gdt_entry){
      (unsigned short) 103,//limite
      (unsigned short) 0,//base
      (unsigned char) 0,//base
      (unsigned char) 9,//Type
      (unsigned char) 0,//Fijo
      (unsigned char) 3,//Nivel 3 
      (unsigned char) 1,//Presente
      (unsigned char) 0,//limite
      (unsigned char) 1,//AVL DUDA!!
      (unsigned char) 0,//FIJO
      (unsigned char) 0,//FIJO
      (unsigned char) 0,//granularity 1b 
      (unsigned char) 0 //base
    },
/* TSS Tarea 5 - Indice = 5 */
    (gdt_entry){
      (unsigned short) 103,//limite
      (unsigned short) 0,//base
      (unsigned char) 0,//base
      (unsigned char) 9,//Type
      (unsigned char) 0,//Fijo
      (unsigned char) 3,//Nivel 3 
      (unsigned char) 1,//Presente
      (unsigned char) 0,//limite
      (unsigned char) 1,//AVL DUDA!!
      (unsigned char) 0,//FIJO
      (unsigned char) 0,//FIJO
      (unsigned char) 0,//granularity 1b 
      (unsigned char) 0 //base
    },
/* TSS Tarea Inicial - Indice = 6 */
    (gdt_entry){
      (unsigned short) 103,//limite
      (unsigned short) 0,//base
      (unsigned char) 0,//base
      (unsigned char) 9,//Type
      (unsigned char) 0,//Fijo
      (unsigned char) 0,//Nivel 0 
      (unsigned char) 1,//Presente
      (unsigned char) 0,//limite
      (unsigned char) 1,//AVL DUDA!!
      (unsigned char) 0,//FIJO
      (unsigned char) 0,//FIJO
      (unsigned char) 0,//granularity 1b 
      (unsigned char) 0 //base
    },
/* TSS Tarea Idle - Indice = 7 */
    (gdt_entry){
      (unsigned short) 103,//limite
      (unsigned short) 0,//base
      (unsigned char) 0,//base
      (unsigned char) 9,//Type
      (unsigned char) 0,//Fijo
      (unsigned char) 0,//Nivel 0 
      (unsigned char) 1,//Presente
      (unsigned char) 0,//limite
      (unsigned char) 1,//AVL DUDA!!
      (unsigned char) 0,//FIJO
      (unsigned char) 0,//FIJO
      (unsigned char) 0,//granularity 1b
      (unsigned char) 0 //base
    },

	/* Ponemos en 0 los descriptores correspondientes a los indices 8-9 */
	(gdt_entry){(unsigned int) 0x00000000, (unsigned int) 0x00000000 },
	(gdt_entry){(unsigned int) 0x00000000, (unsigned int) 0x00000000 },
	
	/* Descriptor de Codigo nivel 0 - Indice = 10 */
    (gdt_entry){
      (unsigned short) 65536,
  		(unsigned short) 0,//base                        
  		(unsigned char) 0,//base 
  		(unsigned char) 10,//Execute/Read 
  		(unsigned char) 1,//No sistema 
  		(unsigned char) 0,//Nivel 0 
  		(unsigned char) 1,//Presente 
  		(unsigned char) 7, //limite
		(unsigned char) 0,  			//avl
		(unsigned char) 0,  			//l
  		(unsigned char) 1,//32 bits  
  		(unsigned char) 1,//granularity 4kb
  		(unsigned char) 0 //base
  	},
	/* Descriptor de Datos nivel 0 - Indice = 11 */
  	(gdt_entry){
  		(unsigned short) 65536,
  		(unsigned short) 0, //base
  		(unsigned char) 0, //base
  		(unsigned char) 2,//Read/Write
  		(unsigned char) 1,//NO sistema 
  		(unsigned char) 0,//Nivel 0 
  		(unsigned char) 1,//Presente 
  		(unsigned char) 7, //limite
		(unsigned char) 0,  			//avl
		(unsigned char) 0,  			//l
  		(unsigned char) 1,//32 bits 
  		(unsigned char) 1,//granularity 4kb
  		(unsigned char) 0 //base
  	},
	/* Descriptor de Codigo nivel 3 - Indice = 12 */
  	(gdt_entry){
  		(unsigned short) 65536,
  		(unsigned short) 0,//base
  		(unsigned char) 0, //base
  		(unsigned char) 10,//Execute/Read
  		(unsigned char) 1,//No sistema
  		(unsigned char) 3,//Nivel 
  		(unsigned char) 1,//Presente 
  		(unsigned char) 7, //limite
		(unsigned char) 0,  			//avl
		(unsigned char) 0,  			//l
  		(unsigned char) 1,//32 bits
  		(unsigned char) 1,//granularity 4kb 
  		(unsigned char) 0 //base
  	},
	/* Descriptor de Datos nivel 3 - Indice = 13 */
  	(gdt_entry){
  		(unsigned short) 65536,
  		(unsigned short) 0, //base
  		(unsigned char) 0, //base
  		(unsigned char) 2,//Read/Write
  		(unsigned char) 1,//No sistema
  		(unsigned char) 3,//Nivel 3 
  		(unsigned char) 1,//Presente
  		(unsigned char) 7, //limite
		(unsigned char) 0,  			//avl
		(unsigned char) 0,  			//l
  		(unsigned char) 1,//32 bits
  		(unsigned char) 1,//granularity 4kb 
  		(unsigned char) 0 //base
  	},
	/* Descriptor de Video nivel 0 - Indice = 14 */
    (gdt_entry){
      (unsigned short) 4000, //limite
      (unsigned short) 0x8000, //base
      (unsigned char) 0xB, //base
      (unsigned char) 2,//Read/Write
      (unsigned char) 1,//No sistema
      (unsigned char) 0,//Nivel 0 
      (unsigned char) 1,//Presente
      (unsigned char) 0, //limite
		(unsigned char) 0,  			//avl
		(unsigned char) 0,  			//l
      (unsigned char) 1,//32 bits
      (unsigned char) 0,//granularity 1b 
      (unsigned char) 0 //base
    },
  };

gdt_descriptor GDT_DESC = {sizeof(gdt)-1, (unsigned int)&gdt};
