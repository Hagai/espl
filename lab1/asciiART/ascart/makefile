asciiART: font.o prsym.o
	gcc -o asciiART font.o prsym.o

font.o: font.h font.c
	gcc -c -o font.o font.c

prsym.o: font.h prsym.c
	gcc -c -o prsym.o prsym.c

clean:
	rm *.o
	rm asciiART
