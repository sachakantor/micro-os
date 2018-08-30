/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/
#include "defines.h"

#include "i386.h"

LS_INLINE void set_shared(unsigned int val) {
	__asm __volatile("mov %0, %%ebx": : "r" (val) );
	__asm __volatile("mov $286, %eax");
	__asm __volatile("int $69");
}

LS_INLINE unsigned int get_code(void) {
	unsigned int val;
	__asm __volatile("mov $386, %eax");
	__asm __volatile("int $69");
	__asm __volatile("mov %%ecx, %0" : "=r" (val));
	return val;
}

LS_INLINE unsigned int get_stack(void) {
	unsigned int val;
	__asm __volatile("mov $386, %eax");
	__asm __volatile("int $69");
	__asm __volatile("mov %%edx, %0" : "=r" (val));
	return val;
}

void task(){

//    breakpoint();

	/* ///////////////////////////////////////////////// */
	/* llama a los servicios del OS con cualquier parametro */
	#ifdef task1
	__asm __volatile("mov $28, %eax");
	__asm __volatile("int $69");
	#endif

	/* ///////////////////////////////////////////////// */
	/* hace una division por cero */
	#ifdef task2
	__asm __volatile("mov $0, %eax");
	__asm __volatile("mov $0, %ebx");
	__asm __volatile("div %ebx");
	#endif

	/* ///////////////////////////////////////////////// */
	/* mapea paginas todo el tiempo */
	#ifdef task3
	int t=0;
	while(1) { for(t=1;t<100;t++) set_shared(t%100); }
	#endif

	/* ///////////////////////////////////////////////// */
	/* intenta direcionar un puntero null */
	/* (despues de un rato de recorrer paginas) */
	#ifdef task4
	unsigned int *null = 0;
	*null=0;
	#endif

	/* ///////////////////////////////////////////////// */
	/* pisa una a una todas las paginas de otras tareas */
	#ifdef task5
	int i, j;
	unsigned int code, stack;
	unsigned int *dest;
	code  = get_code();
	stack = get_stack();
	while(1) {
		for(i = 99; i >= 0; i--){
			if( i!=code && i!=stack ) {
				set_shared(i);
				dest = (unsigned int*)TASK_SHARE;
				for(j=0;j<1024;j++) dest[j] = 0xffffffff;
		}	}	};
	#endif

	while(1) {};
}
