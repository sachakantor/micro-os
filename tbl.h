/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las tablas de paginas
*/

#ifndef __TBL_H__
#define __TBL_H__
/*typedef struct str_tbl_descriptor {
	unsigned char zeros:3;
	unsigned char pwt:1;
	unsigned char pcd:1;
	unsigned char reservados:7;
	unsigned int base_tbl:20;
} __attribute__((__packed__)) tbl_descriptor;
*/
typedef struct str_tbl_entry {
	unsigned char p:1;
	unsigned char rw:1;
	unsigned char us:1;
	unsigned char pwt:1;
	unsigned char pcd:1;
	unsigned char a:1;
	unsigned char d:1;
	unsigned char pat:1;
	unsigned char g:1;
	unsigned char disponible:3;
	unsigned int base_pag:20;
} __attribute__((__packed__, aligned (4))) tbl_entry;

/** Tabla TBL **/
//extern tbl_entry tbl[];
//extern tbl_descriptor DIR_DESC;

#define TBL_COUNT 1024
#endif //__TBL_H__:w!
