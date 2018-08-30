/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la directorio/tablas de paginas
*/

#ifndef __PAG_H__
#define __PAG_H__

#define DIR_COUNT 1024
#define TBL_COUNT 1024

//Definicion de entradas del directorio y de las tablas
typedef struct str_dir_entry {
	unsigned char p:1;
	unsigned char rw:1;
	unsigned char us:1;
	unsigned char pwt:1;
	unsigned char pcd:1;
	unsigned char a:1;
	unsigned char zero:1;
	unsigned char ps:1;
	unsigned char g:1;
	unsigned char disponible:3;
	unsigned int base_tbl:20;
} __attribute__((__packed__, aligned (4))) dir_entry; //alineamos a 4 pues es el tamaño de la entrada

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
} __attribute__((__packed__, aligned (4))) tbl_entry; //alineamos a 4 pues es el tamaño de la entrada

//Funciones para crear entradas
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
                    );

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
                    );

//Variables/Funciones globales que otros .c han de usar
extern dir_entry* pdt[];
extern tbl_entry* ptt[];
extern int* ts[];

#endif //__PAG_H__
