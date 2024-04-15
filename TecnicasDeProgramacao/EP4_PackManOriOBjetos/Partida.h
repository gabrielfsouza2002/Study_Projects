#pragma once

using namespace std;
/*!
* \brief Classe responsavel por desenvolver todo o jogo.
*/
class Partida {

private:
    /*!
    * \brief Classe responsavel por desenvolver todo o jogo.
    */
    int movimento;
    /*!
    * \brief Classe responsavel por desenvolver todo o jogo.
    */
    int pontos;
    /*!
    * \brief Classe responsavel por desenvolver todo o jogo.
    */
    int status;

public:
    /*!
    * \brief Classe responsavel por desenvolver todo o jogo.
    * \return retorna um inteiro que representa a quantidade total de pacdots do tabuleiro.
    */
    int ContPacDots(char** laberinto, int qtdlinhas, int qtdcolunas, int conta_fantasmas);
    /*!
    * \brief Essa funcao ira ser responsavel pela execucao do jogo.
    */
    void Play(int argc, char **argv);
};

