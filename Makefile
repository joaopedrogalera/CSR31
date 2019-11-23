###########################MAKEFILE#########################
all:envia recebe
envia: envia.o
	gcc -o envia envia.o

envia.o: envia.c
	gcc -c envia.c -Wall

recebe: recebe.o
	gcc -o recebe recebe.o

recebe.o: recebe.c
	gcc -c recebe.c -Wall

clean:
	rm -rf *.o

mrproper: clean
	rm -rf envia recebe
