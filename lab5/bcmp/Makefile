%.o: %.asm
	nasm -g -f elf -o $@ $<

%.o: %.c
	gcc -m32 -g -nostdlib -fno-stack-protector -c -o $@ $<

.PHONY: clean all

all: ahalan

ahalan: start.o main.o ahalan.o sys_puts.o length.o
	ld -melf_i386 -g -o $@ $^

length.o:length.c
sys_puts.o: sys_puts.asm
ahalan.o: ahalan.asm
start.o: start.asm
main.o: main.c

clean:
	rm *.o ahalan
