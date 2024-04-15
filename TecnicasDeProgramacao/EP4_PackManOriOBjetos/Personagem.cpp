#include <iostream>
#include <random>
#include <gtest/gtest.h>
#include <fstream>
#include "Personagem.h"
using namespace std;

void Personagem::MovimentaPersonagem(int x, int y, char direcao[1], int qtdlinhas, int qtdcolunas){

    switch (direcao[0])
    {
    case 'd':
    this->y = y+1;
    this->x =x;
    break;
    case 'a':         
    this->y = y-1;
    this->x =x;
    break;
    case 's':
    this->x = x+1;
    this->y = y;
    break;
    case 'w':
    this->x = x-1;
    this->y = y;
    break;                                        
    default:
    cout << "<Selecione uma direcao valida>" << endl;
    break;
    }
    if ((y == qtdcolunas-1) && ((this->y)-y > 0)){
    this->y = 0;

    }
    else if ((y == 0) && ((this->y)-y < 0)){
    this->y = qtdcolunas-1;
    }
    else if ((x == qtdlinhas) && ((this->x)-x > 0)){
    this->x = 0;    
    } 
    else if ((x == 0) && ((this->x)-x < 0)){
    this->x = qtdlinhas-1;
    } 
}
void Personagem::morre(){
this->status = 0;
}
int Personagem::getStatus(){
return this->status;
}
int Personagem::getX(){
return this->x;
}
int Personagem::getY(){
return this->y;
}

void Personagem::setSprite(char sprite){
this->sprite[0]= sprite;
}
void Personagem::setStatus(int status){
this->status = status;
}