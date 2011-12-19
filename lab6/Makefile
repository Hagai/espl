obj = 

%.o: %.asm
	nasm -g -f elf -o $@ $<

%.o: %.c
	gcc -m32 -g -fno-stack-protector -c -o $@ $<

.PHONY: clean all

all: prsym

prsym:  char2int.o length.o sys_puts.o sys_putsl.o start.o font.o main.o mystrlen.o print_letter.o#sys_puts.o length.o
	ld -melf_i386 -g -o $@ $^

print_letter.o:print_letter.asm
mystrlen.o:mystrlen.asm
length.o:length.c
sys_puts.o: sys_puts.asm
sys_putsl.o: sys_putsl.asm
start.o: start.asm
font.o: font.c
font.c:font.h
main.o: main.c
char2int.o:char2int.asm


#prsym.o: prsym.asm




clean:
	rm *.o prsym
