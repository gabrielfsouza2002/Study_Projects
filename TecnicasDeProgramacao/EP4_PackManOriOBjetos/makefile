# Makefile
CC=g++
CFLAGS= -Wall
DOC=doxygen
AR=ar
ARFLAGS= -rcv

################################

OBJS=Arquivo.o Laberinto.o Personagem.o Fantasma.o Pacman.o Partida.o
DOXYFILE=Doxyfile
LIB=libep4.a
MAIN=ep4.cpp

################################

.PHONY: clean

all: jogo

Arquivo.o: Arquivo.h

Laberinto.o: Laberinto.h

Personagem.o: Personagem.h

Fantasma.o: Fantasma.h Personagem.h

Pacman.o: Pacman.h Pacman.h

Partida.o: Partida.h

${LIB}: ${OBJS}
	${AR} ${ARFLAGS} ${LIB} ${OBJS}

jogo: ${OBJS} ${LIB} ${MAIN}
	${CC} ${CFLAGS} -o ep4 ${MAIN} ${LIB}

html: 
	${DOC} ${DOXYFILE}

clean:
	@rm -rf *.o html *.a par_impar
