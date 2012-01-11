# generic rule for compiling C files

CFLAGS=-g -O -Wall
TARGET=elfheader

%.o: %.c
	gcc -c $(CFLAGS) -o $@ $<

%: %.o
	gcc $(CFLAGS) -o $@ $<

all: clean $(TARGET)

$(TARGET): $(TARGET).o

clean:
	rm -f *.o

distclean: clean
	rm -f $(TARGET) *~ *.o
