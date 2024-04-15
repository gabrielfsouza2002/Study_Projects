#pragma once
#include "Personagem.h"

using namespace std;
/*!
* \brief Essa classe herda a classe Personagem. Ela representa o Pacman.
*/
class Pacman: public Personagem {

protected:
    /*!
    * \brief pacdots que ja foram comidos pelo Pacman.
    */
    int pac_dots_comidos;
    /*!
    * \brief char que representa a posicao anterior do Pacman.
    */
    char posiAnt[1];

public:
    /*!
    * \brief Construtor do Pacman.
    */
    Pacman();
    /*!
    * \brief Destrutor do Pacman.
    */
    ~Pacman();
    /*!
    * \brief Essa funcao insere o Pacman no laberinto na posicao do meio.
    */
    void InserePacMan(char** laberinto, int qtdlinhas, int qtdcolunas, int *x, int *y);
    /*!
    * \brief ESsa funcao movimenta o Pacman da forma devida.
    */
    void MovimentaPacMan(char** laberinto, int x, int y, int *new_x, int *new_y, char direcao[1],int qtdlinhas, int qtdcolunas);
    /*!
    * \brief Essa funcao conta os pacdots que foram comidos pelo Pacman.
    * \return retorna um inteiro que representa os pacdots comiddos pelo Pacman.
    */
    int cont_pacdots_comidos();
};


