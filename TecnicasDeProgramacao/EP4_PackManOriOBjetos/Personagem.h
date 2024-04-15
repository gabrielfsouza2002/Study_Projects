#pragma once

using namespace std;
/*!
* \brief Classe dos personagens do jogo (Fantasma e o Pacman).
*/
class Personagem{

   protected:
      /*!
      * \brief Posição do personagem em relação a linha do laberinto.
      */      
      int x;
      /*!
      * \brief Posição do personagem em relação a coluna do laberinto.
      */      
         int y;
      /*!
      * \brief Situação do personagem (Vivo ou Morto).
      */      
      int status;
      /*!
      * \brief Caracter que representa o personagem.
      */      
      char sprite[1];

   public:
   /*!
   * \brief Função que faz os personagens se movimentarem da forma adequada.
   */  
    void MovimentaPersonagem(int x, int y, char direcao[1], int qtdlinhas, int qtdcolunas);
   /*!
   * \brief Função que faz o personagem 'morrer'
   */    
    void morre();
   /*!
   * \brief Pega a situação atual do personagem.
   * \return retorna um inteiro que representa o status do personagem (0=morto e 1=vivo).
   */    
    int getStatus();
   /*!
   * \brief Pega a posição x atual do personagem.
   * \return retorna um inteiro que representa a posicao x do personagem.
   */    
    int getX();
   /*!
   * \brief Pega a posição y atual do personagem.
   * \return retorna um inteiro que representa a posicao y do personagem.
   */    
    int getY();
   /*!
   * \brief insere o caracter que ira representar o personagem.
   */    
    void setSprite(char sprite);
   /*!
   * \brief insere a situação atual do personagem.
   */    
    void setStatus(int status);
};


