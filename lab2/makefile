CC = gcc
CFLAGS = 
OBJECTS = complines.o

complines : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o complines

%.o : %.c
	$(CC) $(CFLAGS) -c $<

