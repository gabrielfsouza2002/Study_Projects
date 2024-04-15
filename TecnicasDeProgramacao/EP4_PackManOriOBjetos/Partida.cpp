#include <iostream>
#include <random>
#include <gtest/gtest.h>
#include <fstream>
#include "Partida.h"
#include "Fantasma.h"
#include "Pacman.h"
#include "Laberinto.h"

using namespace std;

int Partida::ContPacDots(char** laberinto, int qtdlinhas, int qtdcolunas, int conta_fantasmas) {

    int i, j;
    int cont = conta_fantasmas;
    for (i = 0; i < qtdlinhas; i++) {
        for (j=0; j < qtdcolunas; j++) {
            if (laberinto[i][j] == '.')
                cont++;
        }
    }
    return cont;
}

void Partida::Play(int argc, char **argv) {

    char** laberinto;

    int qtdlinhas = atoi(argv[2]);
    int qtdcolunas = atoi(argv[3]);
    char posicoes[256][2];
    char botao[1];
    char direcao[1];
    int i, new_x, new_y;
    int conta_fantasmas,x,y;
    int GameOver = 0;
    int total_pacdots;
    char recomecar[1];

    Fantasma F;
    Pacman C;
    Laberinto l;
    laberinto = l.CriaLaberinto(argc,argv);
    conta_fantasmas = F.ContEidentificaFantasmas(laberinto,qtdlinhas,qtdcolunas,posicoes);
    total_pacdots = ContPacDots(laberinto,qtdlinhas,qtdcolunas,conta_fantasmas);
    movimento = 1;

    C.InserePacMan(laberinto,qtdlinhas,qtdcolunas,&x,&y);
    Fantasma * fantasma;
    fantasma = new Fantasma[conta_fantasmas];

    this->pontos = 0;
    this->movimento = 1;

    cout << endl;
    cout << "### BEM-VINDO AO PAC-MAN ###" << endl;
    cout << endl;
    cout << "Insira qualquer botao e pressione 'Enter' para iniciar o jogo: ";
    cin >> botao[0];
    cout << endl;
    cout << endl;
    cout << "######## MOVIMENTO 0 ########" << endl;

    while(direcao[0]!= '0' && !GameOver) {

        this->pontos = C.cont_pacdots_comidos();

        if(this->pontos == total_pacdots)
            break;

        cout << endl;
        l.ImprimeLaberinto(laberinto,qtdlinhas);
        cout << endl;
        cout << "PacDots Comidos: "<< this->pontos << endl;
        cout << "Digite a direcao: ";
        cin >> direcao[0];
        cout << endl;
        cout << "---------------------------------" << endl;

        C.MovimentaPacMan(laberinto,x,y,&new_x,&new_y,direcao,qtdlinhas,qtdcolunas);
        x = new_x;
        y = new_y;
        if(!C.getStatus())
            GameOver=1;

        for (i = 0; i < conta_fantasmas && C.getStatus(); i++) {
            fantasma[i].MovimentaFantasma(laberinto,posicoes[i][0],posicoes[i][1],&new_x,&new_y,qtdlinhas,qtdcolunas);
            posicoes[i][0] = new_x;
            posicoes[i][1] = new_y;

            if (!fantasma[i].getStatus())
                GameOver=1;
        }

        cout << endl;
        cout << "######## MOVIMENTO "<<this->movimento<<" ########" << endl;
        this->movimento++;
    }

    l.ImprimeLaberinto(laberinto,qtdlinhas);

    if (total_pacdots == this->pontos) {
        cout << endl;
        cout << "VOCE VENCEU!! Pontos: " << this->pontos << endl;
        cout << endl;
        cout << "-------------------------" << endl;
        cout << "Deseja recomecar? Confirme 'y' caso sim ou qualquer outra tecla caso nao: ";
        cin >> recomecar[0];
        cout << endl;
    } else {
        cout << endl;
        cout << "GAME OVER!! Pontos: " << this->pontos << endl;
        cout << endl;
        cout << "-------------------------" << endl;
        cout << "Deseja recomecar? Confirme 'y' caso sim ou qualquer outra tecla caso nao: ";
        cin >> recomecar[0];
        cout << endl;
    }

    if (recomecar[0] == 'y')
        Play(argc, argv);
    else
        cout << "FIM DE JOGO!" << endl;

    return;
}

