###########################MAKEFILE#########################
all:envia
csr31: envia.o
	gcc -o csr31 envia.o

envia.o: envia.c
	gcc -c envia.c -Wall

clean:
	rm -rf *.o

mrproper: clean
	rm -rf csr31
