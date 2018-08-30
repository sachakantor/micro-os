#!/bin/bash

#define  INIT_LUCHA  0x100000 /* direccion de comienzo del espacio de lucha */
#define   END_LUCHA  0x163000 /* direccion de final del espacio de lucha */

file=rand_.c

seguir=0;

while [[ $seguir == 0 ]]
do
	seguir=1;

	a[0]=$[ ($RANDOM % 100) * 4096 + 1048576 ]
	a[1]=$[ ($RANDOM % 100) * 4096 + 1048576 ]
	a[2]=$[ ($RANDOM % 100) * 4096 + 1048576 ]
	a[3]=$[ ($RANDOM % 100) * 4096 + 1048576 ]
	a[4]=$[ ($RANDOM % 100) * 4096 + 1048576 ]
	a[5]=$[ ($RANDOM % 100) * 4096 + 1048576 ]
	a[6]=$[ ($RANDOM % 100) * 4096 + 1048576 ]
	a[7]=$[ ($RANDOM % 100) * 4096 + 1048576 ]
	a[8]=$[ ($RANDOM % 100) * 4096 + 1048576 ]
	a[9]=$[ ($RANDOM % 100) * 4096 + 1048576 ]

	for i in $( seq 0 9 )
	do
		for j in $( seq $[$i+1] 9 )
		do
			if [[ ${a[$i]} == ${a[$j]} ]]
			then
				seguir=0
				echo "otra vez!"
			fi
		done
	done
done

echo "//NO MODIFICAR ESTE ARCHIVO, CREADO AUTOMAGICAMENTE" > $file

echo "unsigned int pc[] =" >> $file
echo "{"          >> $file
echo "  ${a[0]}," >> $file
echo "  ${a[1]}," >> $file
echo "  ${a[2]}," >> $file
echo "  ${a[3]}," >> $file
echo "  ${a[4]}," >> $file
echo "};"         >> $file
echo "unsigned int ps[] =" >> $file
echo "{"          >> $file
echo "  ${a[5]}," >> $file
echo "  ${a[6]}," >> $file
echo "  ${a[7]}," >> $file
echo "  ${a[8]}," >> $file
echo "  ${a[9]}," >> $file
echo "};"         >> $file
echo "unsigned int px[] =" >> $file
echo "{"          >> $file
echo "  ${a[0]}," >> $file
echo "  ${a[1]}," >> $file
echo "  ${a[2]}," >> $file
echo "  ${a[3]}," >> $file
echo "  ${a[4]}," >> $file
echo "};"         >> $file

