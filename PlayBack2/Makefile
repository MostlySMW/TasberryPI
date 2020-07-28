
ARMGNU ?= arm-none-eabi
#ARMGNU ?= arm-linux-gnueabi

AOPS = --warn --fatal-warnings
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding

all : kernel.img

clean :
	rm -f notmain.o
	rm -f *.bin
	rm -f *.hex
	rm -f notmain.srec
	rm -f notmain.elf
	rm -f notmain.list
	rm -f kernel.img
	rm -f vectors.o

vectors.o : vectors.s
	$(ARMGNU)-as $(AOPS) vectors.s -o vectors.o

notmain.o : notmain.c
	$(ARMGNU)-gcc $(COPS) -c notmain.c -o notmain.o

notmain.elf : memmap vectors.o notmain.o
	$(ARMGNU)-ld vectors.o notmain.o -T memmap -o notmain.elf
	$(ARMGNU)-objdump -D notmain.elf > notmain.list

kernel.img : notmain.elf
	$(ARMGNU)-objcopy --srec-forceS3 notmain.elf -O srec notmain.srec
	$(ARMGNU)-objcopy notmain.elf -O binary kernel.img

