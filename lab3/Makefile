gcc:
	gcc -g main.c contvector.c ../lab1s2/datatime.c ../lab2s2/bitstruct.c -o 1.o
clean:
	rm -f *.o
run: gcc
	leaks --atExit -- ./1.o
