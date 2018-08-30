/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/

#ifndef __ISR_H__
#define __ISR_H__

/* Libreria para la magia negra de las macros */
#include "repeat.hpp"

/* Lo siguiente es una macro DE EJEMPLO para ayudar a armar entradas de interrupciones */
/* Para usar, completar correctamente los atributos y el registro de segmento */
#define NEW_INT(z, numero, text) \
	void _isr ## numero();

/* La siguiente macro lo que hace es llamar a la macro que se le pasa por parametro, la cantidad de veces
 * que se le indique en el primer parametro (comienza desde 0). A su vez, es primer parametro
 * sera el primer parametro de la macro definida en el segundo parametro.
 *
 * Para mas detalles:
 * http://www.boost.org/doc/libs/1_52_0/libs/preprocessor/doc/index.html
 */
BOOST_PP_REPEAT(20, NEW_INT, 'x')

void reloj();
void teclado();
void serviciosOS();
void indiceArenaNoValido();

#endif // __ISR_H__
