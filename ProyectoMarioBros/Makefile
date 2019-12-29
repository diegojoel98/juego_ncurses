CC = gcc
CFLAGS = -Wall -g
INCLUDES = -I ./include

all: ejLecturaMapa 

objs/Lista_ListaCircular.o: Lista_ListaCircular.c include/Lista_ListaCircular.h
	$(CC) $(CFLAGS) -c $(INCLUDES) -o objs/Lista_ListaCircular.o Lista_ListaCircular.c 

objs/ejLecturaMapa.o: ./ejLecturaMapa.c include/Lista_ListaCircular.h
	$(CC) $(CFLAGS) -c $(INCLUDES) -o objs/ejLecturaMapa.o ejLecturaMapa.c

ejLecturaMapa: objs/ejLecturaMapa.o objs/Lista_ListaCircular.o
	$(CC) $(CFLAGS) -g -o ejLecturaMapa objs/ejLecturaMapa.o objs/Lista_ListaCircular.o -lncurses

clean:
	rm objs/* ejLecturaMapa
