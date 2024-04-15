#include <iostream>
#include <random>
#include <gtest/gtest.h>
#include <fstream>
#include "Fantasma.h"


using namespace std;

Fantasma::Fantasma() {

    this->setSprite('F');
    this->setStatus(1);
    this->posiAnt[0] = '.';
}
Fantasma::~Fantasma() {
    morre();
}

int Fantasma::ContEidentificaFantasmas(char** laberinto, int qtdlinhas, int qtdcolunas, char posicoes[256][2]) {
    int i, j;
    int cont = 0;
    for (i = 0; i < qtdlinhas; i++) {
        for (j = 0; j < qtdcolunas; j++) {

            if (laberinto[i][j] == sprite[0]) {
                posicoes[cont][0] = i;
                posicoes[cont][1] = j;
                cont++;
            }
        }
    }
    return cont;
}

void Fantasma::MovimentaFantasma(char** laberinto, int x, int y, int *new_x, int *new_y, int qtdlinhas, int qtdcolunas) {

    laberinto[x][y] = this->posiAnt[0];
    int j=0;
    int direcao;
    char dir[1];
    srand(time(NULL));

    while(j<5) {

        this->x = x;
        this->y = y;

        direcao = rand()%4;

        switch (direcao)
        {
        case 0:
            dir[0] = 'a';
            break;
        case 1:
            dir[0] = 'w';
            break;
        case 2:
            dir[0] = 'd';
            break;
        case 3:
            dir[0] = 's';
            break;

        default:
            break;
        }

        MovimentaPersonagem(x, y, dir,qtdlinhas,qtdcolunas);

        if (laberinto [this->x][this->y] == '.' || laberinto [this->x][this->y] == ' ' || laberinto [this->x][this->y] == 'C') {
            if (laberinto [this->x][this->y] == 'C') {
                morre();
                laberinto [this->x][this->y] = 'X';
                laberinto [x][y] = this->posiAnt[0];
                return;
            }
            this->posiAnt[0] = laberinto [this->x][this->y];
            laberinto[this->x][this->y] = sprite[0];
            *new_x = this->x;
            *new_y = this->y;
            break;;
        }
        j++;
    }
    if (j >= 5) {
        *new_x = x;
        *new_y = y;
        laberinto[x][y] = sprite[0];
    }
}
