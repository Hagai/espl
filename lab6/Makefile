%.o: %.asm
	nasm -g -f elf -o $@ $<

%.o: %.c
	gcc -m32 -g -fno-stack-protector -c -o $@ $<

.PHONY: clean all

all: prsym

prsym:  char2int.o length.o sys_puts.o sys_putsl.o start.o font.o main.o mystrlen.o print_letter.o print_word.o #sys_puts.o length.o
	ld -melf_i386 -g -o $@ $^



start.o: start.asm
mystrlen.o:mystrlen.asm
sys_puts.o: sys_puts.asm
sys_putsl.o: sys_putsl.asm
print_letter.o:print_letter.asm
print_word.o:print_word.asm
char2int.o:char2int.asm
#length.o:length.c
font.o: font.c
font.c:font.h
main.o: main.c



#prsym.o: prsym.asm




clean:
	rm *.o prsym
