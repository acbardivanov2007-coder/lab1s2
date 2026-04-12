CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = demo
OBJS = main.o datatime.o bitstruct.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c datatime.h bitstruct.h
	$(CC) $(CFLAGS) -c main.c

datatime.o: datatime.c datatime.h
	$(CC) $(CFLAGS) -c datatime.c

bitstruct.o: bitstruct.c bitstruct.h datatime.h
	$(CC) $(CFLAGS) -c bitstruct.c

clean:
	rm -f *.o $(TARGET)
