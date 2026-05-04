CC = gcc
CFLAGS = -Wall -Wextra

all: demo

demo: main.o fiodevice.o vector.o device.o
	$(CC) $(CFLAGS) -o main main.o fiodevice.o vector.o device.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

fiodevice.o: fiodevice.c
	$(CC) $(CFLAGS) -c fiodevice.c

vector.o: vector.c
	$(CC) $(CFLAGS) -c vector.c

device.o: device.c
	$(CC) $(CFLAGS) -c device.c

clean:
	rm -f *.o main
