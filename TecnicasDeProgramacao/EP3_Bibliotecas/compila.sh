#!/bin/bash -x

function verifica {
 if [ $? -ne 0 ]; then
 echo "A compilação falhou!"
 exit 1
 fi
}

#Criando biblioteca estática.
gcc -Wall -c -o propriedadesnumericas.o propriedadesnumericas.c
verifica
ar -rcv propriedadesnumericas.a propriedadesnumericas.o
verifica

#Criando biblioteca dinâmica.
export LD_LIBRARY_PATH=/path/to/libs:$LD_LIBRARY_PATH
verifica
gcc -c -fPIC -o VetorAleatorio.o VetorAleatorio.c
verifica
gcc -o libvetoraleatorio.so -shared VetorAleatorio.o
verifica
gcc -o teste teste.c -L${PWD} -lvetoraleatorio
verifica
if [ "$1" == "desliga_assert" ]; then
    gcc -Wall -DNDEBUG -o teste teste.c propriedadesnumericas.a libvetoraleatorio.so
    verifica
else
    gcc -Wall -o teste teste.c propriedadesnumericas.a libvetoraleatorio.so
    verifica
fi

doxygen Doxyfile

./teste
exit 0
