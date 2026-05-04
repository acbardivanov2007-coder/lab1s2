CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: demo

demo: main.o vector.o
	$(CC) $(CFLAGS) main.o vector.o -o demo

main.o: main.c vector.h device.h
	$(CC) $(CFLAGS) -c main.c

vector.o: vector.c vector.h device.h
	$(CC) $(CFLAGS) -c vector.c

clean:
	rm -f *.o demo
