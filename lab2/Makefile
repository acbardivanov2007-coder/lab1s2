# Итоговый файл программы будет называться demo
demo: main.o datatime.o device.o
	gcc main.o datatime.o device.o -o demo

# Правила сборки каждого отдельного файла:
main.o: main.c datatime.h device.h
	gcc -c main.c

datatime.o: datatime.c datatime.h device.h
	gcc -c datatime.c

device.o: device.c device.h
	gcc -c device.c

# Цель для очистки временных файлов
clean:
	rm -f *.o demo
