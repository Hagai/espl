
canalyze: fgetname.o namelist.o canalyze.o
	gcc -o canalyze fgetname.o namelist.o canalyze.o

namelist.o: namelist.h namelist.c
	gcc -c -o namelist.o namelist.c

canalyze.o: canalyze.c
	gcc -c -o canalyze.o canalyze.c

fgetname.o: fgetname.c
	gcc -c -o fgetname.o fgetname.c

clean:
	rm *.o
	rm canalyze
