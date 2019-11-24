###########################MAKEFILE#########################
all:envia recebe
envia: envia.o plotg.o
	gcc -o envia envia.o plotg.o

envia.o: envia.c
	gcc -c envia.c -Wall

recebe: recebe.o plotg.o
	gcc -o recebe recebe.o plotg.o

recebe.o: recebe.c
	gcc -c recebe.c -Wall

plotg.o: plotg.c
	gcc -c plotg.c -Wall

clean:
	rm -rf *.o

mrproper: clean
	rm -rf envia recebe
