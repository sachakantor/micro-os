/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/
#include "defines.h"

#include "isr.h"
#include "idt.h"
#include "i386.h"
#include "screen.h"

/* Libreria para la magia negra de las macros */
#include "repeat.hpp"

/* Lo siguiente es una macro DE EJEMPLO para ayudar a armar entradas de interrupciones */
/* Para usar, completar correctamente los atributos y el registro de segmento */
#define IDT_ENTRY(z, numero, text) \
	idt[numero].offset_0_15 = (unsigned short) ((unsigned int)(&_isr ## numero) & (unsigned int) 0xFFFF); \
	idt[numero].segsel = (unsigned short) CODIGO_0; \
	idt[numero].attr = (unsigned short) 0x8E00; \
	idt[numero].offset_16_31 = (unsigned short) ((unsigned int)(&_isr ## numero) >> 16 & (unsigned int) 0xFFFF);
// numero = offset
//segsel = decimo segmento, que es el de codigo nivel 0
//attr son los atributos. Tenemos dudas en el bit D

void inicializar_idt() {
    /* La siguiente macro lo que hace es llamar a la macro que se le pasa por parametro, la cantidad de veces
     * que se le indique en el primer parametro (comienza desde 0). A su vez, es primer parametro
     * sera el primer parametro de la macro definida en el segundo parametro.
     *
     * Para mas detalles:
     * http://www.boost.org/doc/libs/1_52_0/libs/preprocessor/doc/index.html
     */
    BOOST_PP_REPEAT(20, IDT_ENTRY, 'x')

    //Interrupcion 0x20: Teclado
    idt[32].offset_0_15 = (unsigned short) ((unsigned int)(&reloj) & (unsigned int) 0xFFFF);
    idt[32].segsel = (unsigned short) CODIGO_0;
    idt[32].attr = (unsigned short) 0x8E00;
    idt[32].offset_16_31 = (unsigned short) ((unsigned int)(&reloj) >> 16 & (unsigned int) 0xFFFF);

    //Interrupcion 0x21: Reloj
    idt[33].offset_0_15 = (unsigned short) ((unsigned int)(&teclado) & (unsigned int) 0xFFFF);
    idt[33].segsel = (unsigned short) CODIGO_0;
    idt[33].attr = (unsigned short) 0x8E00;
    idt[33].offset_16_31 = (unsigned short) ((unsigned int)(&teclado) >> 16 & (unsigned int) 0xFFFF);

    //Interrupcion 0x45: Servicios del OS
    idt[69].offset_0_15 = (unsigned short) ((unsigned int)(&serviciosOS) & (unsigned int) 0xFFFF);
    idt[69].segsel = (unsigned short) CODIGO_0; //Ha de ser 0 pues tendra que acceder al espacio del kernel
    idt[69].attr = (unsigned short) 0xEE00; //Pues puede ser llamada por tareas. Sino salta un #GP
    idt[69].offset_16_31 = (unsigned short) ((unsigned int)(&serviciosOS) >> 16 & (unsigned int) 0xFFFF);

    //Interrupcion 0x46: Set Page pidio un indice en la arean invalido
    idt[70].offset_0_15 = (unsigned short) ((unsigned int)(&indiceArenaNoValido) & (unsigned int) 0xFFFF);
    idt[70].segsel = (unsigned short) CODIGO_0; //Ha de ser 0 pues tendra que acceder al espacio del kernel
    idt[70].attr = (unsigned short) 0xEE00; //Pues puede ser llamada por tareas. Sino salta un #GP
    idt[70].offset_16_31 = (unsigned short) ((unsigned int)(&indiceArenaNoValido) >> 16 & (unsigned int) 0xFFFF);
}

idt_entry idt[256] = {};

idt_descriptor IDT_DESC = {sizeof(idt)-1, (unsigned int)&idt};
