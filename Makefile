# ** por compatibilidad se omiten tildes **
# ==============================================================================
# TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
# ==============================================================================

MCOPY=mcopy

KERNEL_SRC=kernel.asm
KERNEL_OBJ=kernel.o
KERNEL_BIN=kernel.bin

DISK_IMG=diskette.img

CFLAGS=-m32 -g -ggdb -Wall -Werror -O0 \
  -fno-zero-initialized-in-bss -fno-stack-protector -ffreestanding

DEPEND_DOC=kernel.asm macrosmodoreal.mac macrosmodoprotegido.mac gdt.c pic.c idt.c paginacion.c isr.asm tss.c mmu.c Makefile gdt.h paginacion.h pic.h idt.h isr.h tss.h mmu.h sched.h screen.h screen.c rand_.c
OBJ_DOC= $(KERNEL_OBJ)  gdt.o paginacion.o pic.o idt.o isr.o mmu.o sched.o tss.o screen.o rand_.o

TASKA=taska.ctsk
TASKSBINSDOC=$(TASKA)
SCREENBUFFER=screen.buf

TASKS=tareas.tsk
TASKSDOC=tareasdoc.tsk
KERNELSIZE=85504
CODESIZE=60928
TASKSSIZE=24576

OBJDUMP=objdump
OBJCOPY=objcopy
CC=gcc
NASM=nasm
NASMFLAGS=-felf32
LD=ld               
LDTASKFLAGS=-s -static -m elf_i386 --oformat binary -b elf32-i386 -e start -Ttext 0x3A0000
LDFLAGS=-static -m elf_i386 --oformat binary -b elf32-i386 -e start -Ttext 0x1200

.PHONY=clean all image tasks imagedoc tasksdoc

all: tasksdoc imagedoc clean

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.asm
	$(NASM) $(NASMFLAGS) -o $@ $^

imagedoc: $(DEPEND_DOC) $(OBJ_DOC)
	@echo 'Linkeando el kernel...'
	$(LD) $(LDFLAGS) -o kernel.bin $(OBJ_DOC)
	@echo ''
	mv kernel.bin kernel.bin.tmp
	dd if=/dev/zero bs=1 count=$(KERNELSIZE) of=kernel.bin status=noxfer
	dd if=kernel.bin.tmp bs=1 count=$(CODESIZE) of=kernel.bin conv=notrunc status=noxfer
	dd if=$(TASKSDOC) bs=1 count=$(TASKSSIZE) seek=$(CODESIZE) conv=notrunc of=kernel.bin status=noxfer
	@echo 'Copiando el $(KERNEL_BIN) a la imagen de diskette\n'
	$(MCOPY) -o -i $(DISK_IMG) $(KERNEL_BIN) ::/ 

clean:
	rm -f *.bin *.o *.ctsko *.ctsk *.tsko kernel.bin.tmp

taska.tsko: taska.c
	$(CC) $(CFLAGS) -c -o $@ $^ 

%.ctsk: %.tsko
	dd if=/dev/zero bs=1 count=4096 of=$@
	$(LD) $(LDTASKFLAGS) -o $@.tmp $^
	dd if=$@.tmp bs=1 count=4096 seek=0 conv=notrunc of=$@
	rm $@.tmp

%.tsk: %.asm
	$(NASM) -fbin -o $@ $^

tasksdoc: $(TASKSBINSDOC)
	./rand.sh
	dd if=$(TASKA) bs=1 count=4K of=$(TASKSDOC) seek=4K status=noxfer conv=notrunc

