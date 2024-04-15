#include <iostream>
#include <random>
#include <gtest/gtest.h>
#include <fstream>
#include "Pacman.h"
using namespace std;

Pacman::Pacman() {
    this->setStatus(1);
    this->setSprite('C');
    this->posiAnt[0] = ' ';
    this->pac_dots_comidos = 0;
}

Pacman::~Pacman() {
    morre();
}

void  Pacman::InserePacMan(char** laberinto, int qtdlinhas, int qtdcolunas, int *x, int *y) {
    *x = qtdlinhas/2;
    *y = qtdcolunas/2;
    laberinto[*x][*y] = sprite[0];
}

void Pacman:: MovimentaPacMan(char** laberinto, int x, int y, int *new_x, int *new_y, char direcao[1],int qtdlinhas, int qtdcolunas) {

    this->x = x;
    this->y = y;

    MovimentaPersonagem(x,y,direcao, qtdlinhas, qtdcolunas);

    if (laberinto[this->x][this->y] != '*') {

        if (laberinto [this->x][this->y]== '.') {
            this->pac_dots_comidos++;
        }
        else if (laberinto [this->x][this->y]== 'F') {
            morre();
            laberinto[this->x][this->y] = 'X';
            laberinto[x][y] = this->posiAnt[0];
            return;
        }

        laberinto[x][y] = this->posiAnt[0];
        laberinto[this->x][this->y] = 'C';
        *new_x = this->x;
        *new_y = this->y;

    } else {
        *new_x = x;
        *new_y = y;
    }
}

int Pacman::cont_pacdots_comidos() {
    return this->pac_dots_comidos;
}

