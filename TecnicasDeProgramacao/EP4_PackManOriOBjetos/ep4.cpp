
#include <iostream>
#include <random>
#include <gtest/gtest.h>
#include <fstream>
#include "Partida.cpp"
#include "Pacman.cpp"
#include "Fantasma.cpp"
#include "Arquivo.cpp"
#include "Laberinto.cpp"
#include "Personagem.cpp"
#define MAX 256

using namespace std;

int main(int argc, char **argv) {

    if (argc!=4) {
        cerr << "Uso: " << argv[0] << " <laberinto.txt>" << " <Quantidade de linhas>" << " <Quantidade de Colunas>" << endl;
        exit (0);
    }

    Partida PacMan;
    PacMan.Play(argc,argv);

    return 0;
}


