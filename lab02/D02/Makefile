CC=gcc
CFLAGS=-Wall

myWC : main.o
	$(CC) $(CFLAGS) main.o -o myWC

main.o : main.c
	$(CC) $(CFLAGS) -c main.c

clean :
	rm -f *.o

.PHONY : clean

