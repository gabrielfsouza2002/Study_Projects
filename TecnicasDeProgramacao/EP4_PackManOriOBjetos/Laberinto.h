#pragma once

using namespace std;

/*!
* \brief Classe responsável pela criação e impressão do laberinto atrás de um arquivo.
*/
class Laberinto {

public:
    /*!
    * \brief Cria um laberinto para o jogo.
    * \return Um char** que ser[a o laberinto.
    */
    char** CriaLaberinto(int argc, char **argv);
    /*!
    * \brief imprime o Laberinto.
    */
    void ImprimeLaberinto(char** laberinto, int qtdlinhas);
};
