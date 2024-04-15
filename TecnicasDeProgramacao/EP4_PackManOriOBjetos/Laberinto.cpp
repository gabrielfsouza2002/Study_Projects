#include <iostream>
#include <random>
#include <gtest/gtest.h>
#include <fstream>
#include "Laberinto.h"
#include "Arquivo.h"
using namespace std;

char** Laberinto::CriaLaberinto(int argc, char **argv) {
    char** laberinto;
    laberinto = (char**)malloc(sizeof(char**) * atoi(argv[2]));

    for (int i = 0; i < atoi(argv[2]); i++)
        laberinto[i] = (char*)malloc(sizeof(char*) * atoi(argv[3]));

    Arquivo arquivo;
    arquivo.LeArquivo(argc,argv,laberinto);
    return laberinto;
}

void Laberinto::ImprimeLaberinto(char** laberinto, int qtdlinhas) {
    int i = 0;
    for (i = 0; i<qtdlinhas; cout << "[" << laberinto[i] << "]" << endl, i++ );
}
