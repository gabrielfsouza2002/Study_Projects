#include <iostream>
#include <random>
#include <gtest/gtest.h>
#include <fstream>
#include "Arquivo.h"
using namespace std;

void Arquivo::LeArquivo(int argc, char **argv, char** laberinto) {

    arquivoTabuleiro.open(argv[1],ios::in);
    for (int i = 0; i < 31; i++) {
        arquivoTabuleiro.getline(laberinto[i],atoi(argv[2]));
    }
}
