all: myCalc

myCalc: myCalc.o atod.o
	gcc -m32 -o myCalc myCalc.o atod.o

myCalc.o: myCalc.c
	gcc -m32 -c -o myCalc.o myCalc.c

atod.o: atod.c
	gcc -c -m32 -S -masm=intel -c -o $@ $<

hsvmhr.o: hsvmhr.asm
	nasm -g -f elf -o $@ $<



clean:
	rm *.o myCalc
