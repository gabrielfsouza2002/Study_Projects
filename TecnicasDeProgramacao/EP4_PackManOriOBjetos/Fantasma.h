#pragma once
#include "Personagem.h"

using namespace std;

/*!
* \brief Essa classe herda a classe Personagem. Ela ira representar os Fantasmas.
*/
class Fantasma: public Personagem {
protected:
    /*!
    * \brief char que representa a posicao anterior do Fantasma.
    */
    char posiAnt[1];

public:
    /*!
    * \brief Construtor do Fantasma.
    */
    Fantasma();
    /*!
    * \brief Destrutor do Fantasma.
    */
    ~Fantasma();
    /*!
    * \brief Funcao que conta a quantidade de fantasmas no tabuleiro e identifica a posicao de cada um.
    * \return retorna um inteiro que representa a quantidade de fantasmas no tabuleiro.
    */
    int ContEidentificaFantasmas(char** laberinto, int qtdlinhas, int qtdcolunas, char posicoes[256][2]);
    /*!
    * \brief Funcao que movimenta os fantasmas da formda devida.
    */
    void MovimentaFantasma(char** laberinto, int x, int y, int *new_x, int *new_y, int qtdlinhas, int qtdcolunas);

};


