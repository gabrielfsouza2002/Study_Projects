#pragma once

using namespace std;

/*!
* \brief Classe que ira ler o arquivo passado.
*/
class Arquivo {

private:

    fstream arquivoTabuleiro;

public:
    /*!
    * \brief Funcao que ira ler o arquivo passado.
    */
    void LeArquivo(int argc, char **argv, char** laberinto);

};
