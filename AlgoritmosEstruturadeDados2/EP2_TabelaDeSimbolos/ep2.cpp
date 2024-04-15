#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <chrono>

using namespace std;
enum Color { RED, BLACK };                                                                                              // Enumeração para as cores dos nós: VERMELHO e PRETO

class Item {
public:
    int ocorrencia;                                                                                                     // Número de ocorrências
    int numLetters;                                                                                                     // Número de letras
    int numUniqueVowels;                                                                                                // Número de vogais únicas
};

class NodeVO {
public:
    string key;                                                                                                         // Chave do nó
    Item value;                                                                                                         // Valor associado à chave
    NodeVO(string key, Item value) {
        this->key = key;                                                                                                // Inicializa a chave com o valor passado como argumento
        this->value = value;                                                                                            // Inicializa o valor com o valor passado como argumento
    }
};

class NodeABB {
public:
    string key;                                                                                                         // Chave do nó
    Item value;                                                                                                         // Valor associado à chave
    NodeABB* left;                                                                                                      // Ponteiro para o nó filho esquerdo
    NodeABB* right;                                                                                                     // Ponteiro para o nó filho direito

    NodeABB(string key, Item value) {
        this->key = key;                                                                                                // Inicializa a chave com o valor passado como argumento
        this->value = value;                                                                                            // Inicializa o valor com o valor passado como argumento
        left = nullptr;                                                                                                 // Define o ponteiro para o nó filho esquerdo como nulo
        right = nullptr;                                                                                                // Define o ponteiro para o nó filho direito como nulo
    }
};

class NodeARN {
public:
    string key;                                                                                                         // Chave do nó
    Item value;                                                                                                         // Valor associado à chave
    NodeARN* left;                                                                                                      // Ponteiro para o nó filho esquerdo
    NodeARN* right;                                                                                                     // Ponteiro para o nó filho direito
    NodeARN* parent;                                                                                                    // Ponteiro para o nó pai
    Color color;                                                                                                        // Cor do nó

    NodeARN(string key, Item value) {
        this->key = key;                                                                                                // Inicializa a chave com o valor passado como argumento
        this->value = value;                                                                                            // Inicializa o valor com o valor passado como argumento
        left = nullptr;                                                                                                 // Define o ponteiro para o nó filho esquerdo como nulo
        right = nullptr;                                                                                                // Define o ponteiro para o nó filho direito como nulo
        parent = nullptr;                                                                                               // Define o ponteiro para o nó pai como nulo
        color = RED;                                                                                                    // Define a cor do nó como VERMELHO
    }
};

class NodeA23 {
public:
    string key1;                                                                                                        // Primeira chave do nó
    string key2;                                                                                                        // Segunda chave do nó
    Item value1;                                                                                                        // Primeiro valor associado à chave
    Item value2;                                                                                                        // Segundo valor associado à chave
    NodeA23* left;                                                                                                      // Ponteiro para o nó filho esquerdo
    NodeA23* middle;                                                                                                    // Ponteiro para o nó filho do meio
    NodeA23* right;                                                                                                     // Ponteiro para o nó filho direito
    NodeA23* parent;                                                                                                    // Ponteiro para o nó pai

    NodeA23(string key, Item value) {
        key1 = key;                                                                                                     // Inicializa a primeira chave com o valor passado como argumento
        value1 = value;                                                                                                 // Inicializa o primeiro valor com o valor passado como argumento
        key2 = "";                                                                                                      // Define a segunda chave como vazia
        value2 = Item();                                                                                                // Define o segundo valor como um objeto Item vazio
        left = nullptr;                                                                                                 // Define o ponteiro para o nó filho esquerdo como nulo
        middle = nullptr;                                                                                               // Define o ponteiro para o nó filho do meio como nulo
        right = nullptr;                                                                                                // Define o ponteiro para o nó filho direito como nulo
        parent = nullptr;                                                                                               // Define o ponteiro para o nó pai como nulo
    }

    NodeA23(string key1, Item value1, string key2, Item value2) {
        this->key1 = key1;                                                                                              // Inicializa a primeira chave com o valor passado como argumento
        this->value1 = value1;                                                                                          // Inicializa o primeiro valor com o valor passado como argumento
        this->key2 = key2;                                                                                              // Inicializa a segunda chave com o valor passado como argumento
        this->value2 = value2;                                                                                          // Inicializa o segundo valor com o valor passado como argumento
        left = nullptr;                                                                                                 // Define o ponteiro para o nó filho esquerdo como nulo
        middle = nullptr;                                                                                               // Define o ponteiro para o nó filho do meio como nulo
        right = nullptr;                                                                                                // Define o ponteiro para o nó filho direito como nulo
        parent = nullptr;                                                                                               // Define o ponteiro para o nó pai como nulo
    }
};

struct NodeTR {
    string key;                                                                                                         // Chave do nó
    Item value;                                                                                                         // Valor associado à chave
    int priority;                                                                                                       // Prioridade do nó
    NodeTR* left;                                                                                                       // Ponteiro para o nó filho esquerdo
    NodeTR* right;                                                                                                      // Ponteiro para o nó filho direito

    NodeTR(string key, Item value) {
        this->key = key;                                                                                                // Inicializa a chave com o valor passado como argumento
        this->value = value;                                                                                            // Inicializa o valor com o valor passado como argumento
        this->priority = rand() % RAND_MAX;                                                                             // Gera uma prioridade aleatória para o nó
        this->left = nullptr;                                                                                           // Define o ponteiro para o nó filho esquerdo como nulo
        this->right = nullptr;                                                                                          // Define o ponteiro para o nó filho direito como nulo
    }
};


class SymbolTable {

private:

    NodeABB* rootABB;                                                                                                   // Ponteiro para a raiz de uma Árvore de Busca Binária
    NodeARN* rootARN;                                                                                                   // Ponteiro para a raiz de uma Árvore Rubro-Negra
    NodeA23* rootA23;                                                                                                   // Ponteiro para a raiz de uma Árvore 2-3
    NodeTR* rootTR;                                                                                                     // Ponteiro para a raiz de uma Árvore de Treap
    vector<NodeVO> nodeVector;                                                                                          // Vetor de nós do tipo NodeVO

    /*======================================ARVORE DE BUSCA BINÁRIA===========================================*/

    NodeABB* addABB(NodeABB* root, string key, Item value) {
        if (root == nullptr) {  // Se a raiz for nula, cria um novo nó com a chave e valor passados como argumentos
            root = new NodeABB(key, value);
            root->value.ocorrencia++; // Aumenta o contador de ocorrências do valor associado à chave
            return root;
        }
        if (key < root->key) // Se a chave for menor que a chave do nó atual, insere na subárvore esquerda
            root->left = addABB(root->left, key, value);
        else if (key > root->key) // Se a chave for maior que a chave do nó atual, insere na subárvore direita
            root->right = addABB(root->right, key, value);
        else {
            root->value = value; // Se a chave já existe, atualiza o valor associado à chave
            root->value.ocorrencia++; // Aumenta o contador de ocorrências do valor associado à chave
        }
        return root;
    }

    NodeABB* findABB(NodeABB* root, string key) {
        if (root == nullptr || root->key == key) // Se a raiz for nula ou a chave do nó atual for igual à chave procurada, retorna o nó atual
            return root;
        if (key < root->key) // Se a chave for menor que a chave do nó atual, busca na subárvore esquerda
            return findABB(root->left, key);
        else // Se a chave for maior que a chave do nó atual, busca na subárvore direita
            return findABB(root->right, key);
    }

    /*=========================================ARVORE RUBRO NEGRA======================================*/

    NodeARN* addARN(NodeARN* root, string key, Item value) {
        if (root == nullptr) { // Se a raiz for nula, cria um novo nó com a chave e valor passados como argumentos
            root = new NodeARN(key, value);
            root->color = RED; // Define a cor do nó como vermelho
            root->value.ocorrencia++; // Aumenta o contador de ocorrências do valor associado à chave
            return root;
        }
        if (root->parent == nullptr)
            root->color = BLACK; // Define a cor da raiz como preto

        if (key < root->key) {
            root->left = addARN(root->left, key, value); // Insere na subárvore esquerda
            root->left->parent = root;
        } else if (key > root->key) {
            root->right = addARN(root->right, key, value); // Insere na subárvore direita
            root->right->parent = root;
        } else {
            root->value = value; // Se a chave já existe, atualiza o valor associado à chave
            root->value.ocorrencia++; // Aumenta o contador de ocorrências do valor associado à chave
            return root;
        }

        // Correção das propriedades da árvore rubro-negra
        if (root->left != nullptr && root->left->color == RED && root->right != nullptr && root->right->color == RED) { //Caso do pai e tio verrmelho
            root->color = RED; // Avô fica vermelho
            root->left->color = BLACK; // Tio fica preto
            root->right->color = BLACK;// Pai fica preto

            if (root->parent == nullptr) {
                root->color = BLACK;
            }
        }
        if (root->right != nullptr && root->right->color == RED && (root->left == nullptr || root->left->color == BLACK)) { // Caso que o novo nó é neto direito, o pai é vermelho e o tio é preto ou nullptr
            if (root->right->right != nullptr && root->right->right->color == RED) {
                root = rotacaoEsquerda(root); // Realiza uma rotação à esquerda
                root->color = BLACK; 
                root->left->color = RED; 
            } else if (root->right->left != nullptr && root->right->left->color == RED) { // Caso em que o novo nó é filho esquerdo
                root->right = rotacaoDireita(root->right); // Realiza uma rotação à direita
                root = rotacaoEsquerda(root); // Realiza uma rotação à esquerda
                root->color = BLACK; 
                root->left->color = RED;
            }
        }
        if (root->left != nullptr && root->left->color == RED && (root->right == nullptr || root->right->color == BLACK)) { // Caso que o novo nó é neto esquerdo, o pai é vermelho e o tio é preto ou nullptr
            if (root->left->left != nullptr && root->left->left->color == RED) {
                root = rotacaoDireita(root); // Realiza uma rotação à direita
                root->color = BLACK;
                root->right->color = RED;
            } else if (root->left->right != nullptr && root->left->right->color == RED) { // Caso em que o novo nó é filho direito
                root->left = rotacaoEsquerda(root->left); // Realiza uma rotação à esquerda
                root = rotacaoDireita(root); // Realiza uma rotação à direita
                root->color = BLACK;
                root->right->color = RED;
            }
        }
        return root;
    }

    NodeARN* rotacaoEsquerda(NodeARN* node) {
        NodeARN* child = node->right; // Armazena o filho direito do nó
        node->right = child->left; // O filho esquerdo do nó se torna o filho direito do nó atual
        if (node->right != nullptr)
            node->right->parent = node; // Atualiza o pai do filho direito

        child->parent = node->parent; // O pai do filho direito se torna o pai do nó atual
        if (node->parent != nullptr) {
            if (node->parent->left == node)
                node->parent->left = child; // Atualiza o filho esquerdo do pai do nó atual
            else
                node->parent->right = child; // Atualiza o filho direito do pai do nó atual
        }

        child->left = node; // O nó atual se torna o filho esquerdo do filho direito
        node->parent = child; // O pai do nó atual se torna o filho direito
        return child; // Retorna o novo nó raiz da subárvore
    }

    NodeARN* rotacaoDireita(NodeARN* node) {
        NodeARN* child = node->left; // Armazena o filho esquerdo do nó
        node->left = child->right; // O filho direito do nó se torna o filho esquerdo do nó atual
        if (node->left != nullptr)
            node->left->parent = node; // Atualiza o pai do filho esquerdo

        child->parent = node->parent; // O pai do filho esquerdo se torna o pai do nó atual
        if (node->parent != nullptr) {
            if (node->parent->right == node)
                node->parent->right = child; // Atualiza o filho direito do pai do nó atual
            else
                node->parent->left = child; // Atualiza o filho esquerdo do pai do nó atual
        }

        child->right = node; // O nó atual se torna o filho direito do filho esquerdo
        node->parent = child; // O pai do nó atual se torna o filho esquerdo
        return child; // Retorna o novo nó raiz da subárvore
    }

    NodeARN* findARN(NodeARN* root, string key) {
        if (root == nullptr || root->key == key) // Se o nó for folha
            return root;
        if (key < root->key) // O nó se encontra a esquerda do root
            return findARN(root->left, key); 
        else
            return findARN(root->right, key); // O nó se encontra a direita do root
    }

    /*======================================AVORE 2,3=============================================*/
    NodeA23* addA23(NodeA23* root, string key, Item value) {
        if (root == nullptr) { // Se a raiz for nula, cria um novo nó com a chave e valor fornecidos
            root = new NodeA23(key, value);
            root->value1.ocorrencia++;
            return root;
        }

        
        while (root->left != nullptr || root->middle != nullptr || root->right != nullptr) { // Se o nó não é uma folha, continua descendo na árvore
            if (key < root->key1) { // Se a chave é menor que a primeira chave do nó, desce pela esquerda
                root->left->parent = root;
                root = root->left;
            } else if (key > root->key1 && key < root->key2) { // Se a chave está entre a primeira e segunda chave do nó, desce pelo meio              
                root->middle->parent = root;
                root = root->middle;
            } else {  // Se a chave é maior que a segunda chave do nó, desce pela direita
                root->right->parent = root;
                root = root->right;
            }
            if (root->key1 == key || root->key2 == key) { // Verifica se a chave já existe no nó atual
                if (root->key1 == key)
                    root->value1.ocorrencia++;
                if (root->key2 == key)
                    root->value2.ocorrencia++;

                while (root->parent != nullptr) // Atualiza os ponteiros até a raiz
                    root = root->parent;
                
                return root;
            }
        }

        if (root->left == nullptr && root->middle == nullptr && root->right == nullptr) { // Se o nó é uma folha, insere a chave nele
            if (root->key2.empty()) { // Se o nó tem apenas uma chave, adiciona a chave2 e o valor2
                if (key < root->key1) {
                    root->key2 = root->key1;
                    root->value2 = root->value1;
                    root->key1 = key;
                    root->value1 = value;
                    root->value1.ocorrencia++;
                } else {
                    root->key2 = key;
                    root->value2 = value;
                    root->value2.ocorrencia++;
                }
            } else  // O nó tem duas chaves, precisa fazer o split
                root = splitA23(root, key, value);
        }

        
        while (root->parent != nullptr) // Atualiza os ponteiros até a raiz
            root = root->parent;

        return root;
    }

    NodeA23* splitA23(NodeA23* node, string key, Item value) {
        
        if (node->parent == nullptr) { // Verifica se o nó é a raiz da árvore

            
            if (key < node->key1){ // Verifica se a chave é menor que a primeira chave do nó
                NodeA23* newRoot = new NodeA23(node->key1, node->value1); // Cria um novo nó raiz e redistribui as chaves e valores
                newRoot->left = new NodeA23(key, Item());
                newRoot->right = new NodeA23(node->key2, node->value2);
                newRoot->right->right = node->right;
                newRoot->right->left = node->middle;

                if(node->left != nullptr && node->left->key1 != "" && node->left->key2 != ""){ // Verifica se o nó filho esquerdo possui duas chaves
                    NodeA23* newRoot2 = new NodeA23(node->left->key1, node->left->value1); // Cria novos nós para redistribuir as chaves e valores
                    NodeA23* newRoot3 = new NodeA23(node->left->key2, node->left->value2);
                    newRoot2->left = node->left->left;
                    newRoot3->left = node->left->middle;
                    newRoot3->right = node->left->right;
                    newRoot->left->left = newRoot2;
                    newRoot->left->right = newRoot3;
                }

                node = newRoot;
                return node;  

            } 
            else if(key > node->key2){ // Verifica se a chave é maior que a segunda chave do nó
                NodeA23* newRoot = new NodeA23(node->key2, node->value2); // Cria um novo nó raiz e redistribui as chaves e valores
                newRoot->left = new NodeA23(node->key1, node->value1);
                newRoot->right = new NodeA23(key, Item());
                newRoot->left->left = node->left;
                newRoot->left->right = node->middle;

                
                if (node->right != nullptr && node->right->key1 != "" && node->right->key2 != ""){ // Verifica se o nó filho direito possui duas chaves                 
                    NodeA23* newRoot2 = new NodeA23(node->right->key1, node->right->value1); // Cria novos nós para redistribuir as chaves e valores
                    NodeA23* newRoot3 = new NodeA23(node->right->key2, node->right->value2);
                    newRoot2->left = node->right->left;
                    newRoot3->left = node->right->middle;
                    newRoot3->right = node->right->right;
                    newRoot->right->left = newRoot2;
                    newRoot->right->right = newRoot3;
                }


                node = newRoot;
                return node;
            }
            
            else{ // A chave está entre a primeira e a segunda chave do nó 
                NodeA23* newRoot = new NodeA23(key, Item());
                newRoot->left = new NodeA23(node->key1, node->value1);
                newRoot->right = new NodeA23(node->key2, node->value2);
                newRoot->right->right = node->right;
                newRoot->left->left = node->left;
                newRoot->value1.ocorrencia++;

                
                if (node->middle != nullptr && node->middle->key1 != "" && node->middle->key2 != ""){ // Verifica se o nó filho do meio possui duas chaves
                    // Cria novos nós para redistribuir as chaves e valores
                    NodeA23* newRoot2 = new NodeA23(node->middle->key1, node->middle->value1);
                    NodeA23* newRoot3 = new NodeA23(node->middle->key2, node->middle->value2);
                    newRoot2->left = node->middle->left;
                    newRoot3->left = node->middle->left;
                    newRoot3->right = node->middle->right;
                    newRoot->right->left = newRoot3;
                    newRoot->left->right = newRoot2;
                }
                else if (node->middle != nullptr){
                    // Verifica se o nó filho do meio possui uma chave
                    // e adiciona ao novo nó raiz
                    if (node->middle->key1 > newRoot->key1)
                        newRoot->right->left = node->middle;
                    else
                        newRoot->left->right - node->middle;
                }

                node = newRoot;
                return node;

            }
        }

    NodeA23* parent = node->parent;
    
    if (parent->key2.empty()) { // Verifica se o nó pai tem uma segunda chave vazia
        
        if (node == parent->left) { // Verifica se o nó é o filho esquerdo do pai
            parent->key2 = parent->key1; // Adiciona a chave e valor no nó pai
            parent->value2 = parent->value1; 

            if(key < node->key1){ // Verifica a posição da nova chave em relação às chaves do nó atual
                parent->key1 = node->key1;
                parent->value1 = node->value1;
                node->key1 = key;
                node->value1 = value;
                node->value1.ocorrencia++;
            } 
            else if (key > node->key2){
                parent->key1 = node->key2;
                parent->value1 = node->value2;
                node->key2 = key;
                node->value2 = value;
                node->value2.ocorrencia++;
            } 
            else{
                parent->key1 = key;
                parent->value1 = value;
                parent->value1.ocorrencia++;
            }       
            parent->left = new NodeA23(node->key1, node->value1); // Cria novos nós para redistribuir as chaves e valores
            parent->right = new NodeA23(node->key2, node->value2);
            parent->left->left = node->left;
            parent->left->right = node->middle;
            parent->right->left = node->middle;
            parent->right->right = node->right;
            return splitA23(parent, parent->key2, parent->value2); // Recursivamente divide o nó pai

        } 
        else if (node == parent->middle){ // Adiciona a chave e valor no nó pai
            parent->key2 = parent->key1;
            parent->value2 = parent->value1;

            if (key < node->key1){ // Verifica a posição da nova chave em relação às chaves do nó atual
                parent->key1 = key;
                parent->value1 = value;
                parent->value1.ocorrencia++;
            } 
            else if (key > node->key2){
                parent->key1 = node->key2;
                parent->value1 = node->value2;
                node->key2 = key;
                node->value2 = value;
                node->value2.ocorrencia++;
            } 
            else{
                parent->key1 = key;
                parent->value1 = value;
                parent->value1.ocorrencia++;
            }          
            parent->left = new NodeA23(node->key1, node->value1); // Cria novos nós para redistribuir as chaves e valores
            parent->right = new NodeA23(node->key2, node->value2);
            parent->left->left = node->left;
            parent->left->right = node->middle;
            parent->right->left = node->middle;
            parent->right->right = node->right;
            return splitA23(parent, parent->key2, parent->value2); // Recursivamente divide o nó pai
        } 
        else{ // Adiciona a chave e valor no nó pai      
            parent->key2 = key;
            parent->value2 = value;
            parent->value2.ocorrencia++;    
            parent->left = new NodeA23(node->key1, node->value1); // Cria novos nós para redistribuir as chaves e valores
            parent->right = new NodeA23(node->key2, node->value2);
            parent->left->left = node->left;
            parent->left->right = node->middle;
            parent->right->left = node->middle;
            parent->right->right = node->right;         
            return splitA23(parent, parent->key2, parent->value2); // Recursivamente divide o nó pai
        }
    } 
    else{ // O nó pai já tem duas chaves
        
        
        if (node == parent->left) { // Verifica se o nó é o filho esquerdo do pai
            parent->key1 = parent->key2; // Adiciona a chave e valor no nó pai
            parent->value1 = parent->value2;
            parent->key2 = parent->key1;
            parent->value2 = parent->value1;

            if (key < node->key1){ // Verifica a posição da nova chave em relação às chaves do nó atual
                parent->key1 = node->key1;
                parent->value1 = node->value1;
                node->key1 = key;
                node->value1 = value;
                node->value1.ocorrencia++;
            } 
            else if (key > node->key2 && key < parent->key2){
                parent->key1 = node->key2;
                parent->value1 = node->value2;
                node->key2 = key;
                node->value2 = value;
                node->value2.ocorrencia++;
            } 
            else{
                parent->key1 = parent->key2;
                parent->value1 = parent->value2;
                parent->key2 = key;
                parent->value2 = value;
                parent->value2.ocorrencia++;
            }     
            parent->left = new NodeA23(node->key1, node->value1); // Cria novos nós para redistribuir as chaves e valores
            parent->middle = new NodeA23(node->key2, node->value2);
            parent->left->left = node->left;
            parent->left->right = node->middle;
            parent->middle->left = node->middle;
            parent->middle->right = node->right;
            return splitA23(parent->parent, parent->key2, parent->value2); // Recursivamente divide o nó pai

        } 
        else if (node == parent->middle){
            parent->key1 = parent->key2; // Adiciona a chave e valor no nó pai
            parent->value1 = parent->value2;

            if (key < node->key1){ // Verifica a posição da nova chave em relação às chaves do nó atual
                parent->key2 = parent->key1;
                parent->value2 = parent->value1;
                parent->key1 = key;
                parent->value1 = value;
                parent->value1.ocorrencia++;
            } 
            else if (key > node->key2 && key < parent->key2){
                parent->key2 = key;
                parent->value2 = value;
                parent->value2.ocorrencia++;
            } 
            else{
                parent->key2 = parent->key2;
                parent->value2 = parent->value2;
                parent->key1 = key;
                parent->value1 = value;
                parent->value1.ocorrencia++;
            }
            parent->left = new NodeA23(node->key1, node->value1); // Cria novos nós para redistribuir as chaves e valores
            parent->middle = new NodeA23(node->key2, node->value2);
            parent->left->left = node->left;
            parent->left->right = node->middle;
            parent->middle->left = node->middle;
            parent->middle->right = node->right;           
            return splitA23(parent->parent, parent->key2, parent->value2); // Recursivamente divide o nó pai

        } 
        else{
            
            parent->key1 = key; // Adiciona a chave e valor no nó pai
            parent->value1 = value;
            parent->value1.ocorrencia++;
            parent->middle = new NodeA23(node->key1, node->value1); // Cria novos nós para redistribuir as chaves e valores
            parent->right = new NodeA23(node->key2, node->value2);
            parent->middle->left = node->left;
            parent->middle->right = node->middle;
            parent->right->left = node->middle;
            parent->right->right = node->right;
            return splitA23(parent->parent, parent->key2, parent->value2); // Recursivamente divide o nó pai
        }
    }
}

    NodeA23* findA23(NodeA23* root, string key) {
        if (root == nullptr || root->key1 == key || root->key2 == key) //Procura um nó que possue a chave para retornar a raiz
            return root;
        if (key < root->key1) // Procura a esquerda
            return findA23(root->left, key);
        else if (key > root->key2)  // Procura a direita
            return findA23(root->right, key);
        else
            return findA23(root->middle, key); // Procura no meio
    }

    /*==============================================ARVORE TREAP========================================*/

    NodeTR* AddTreap(NodeTR* root, string key, Item value) {
        if (root == nullptr) {
            root = new NodeTR(key, value); // Se a raiz for nula, cria um novo nó com a chave e valor fornecidos
            root->value.ocorrencia++;
            return root;
        }
        if (key < root->key) {
            root->left = AddTreap(root->left, key, value); // Se a chave for menor que a chave do nó atual, insere na subárvore esquerda
            if (root->left->priority > root->priority) {
                root = rotacaoDireita(root); // Realiza uma rotação para a direita se a prioridade do filho esquerdo for maior que a do pai
            }
        } else {
            if (key == root->key){
                root->value.ocorrencia++; // Se a chave já existe na treap, incrementa a ocorrência do valor
                return root;
            }
            root->right = AddTreap(root->right, key, value); // Se a chave for maior ou igual à chave do nó atual, insere na subárvore direita
            if (root->right->priority > root->priority) 
                root = rotacaoEsquerda(root); // Realiza uma rotação para a esquerda se a prioridade do filho direito for maior que a do pai
        }
        return root;
    }

    NodeTR* rotacaoDireita(NodeTR* root) {  // Realiza uma rotação para a direita, trocando a raiz com seu filho esquerdo
        NodeTR* newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;
        return newRoot;
    }

    NodeTR* rotacaoEsquerda(NodeTR* root) { // Realiza uma rotação para a esquerda, trocando a raiz com seu filho direito
        NodeTR* newRoot = root->right; 
        root->right = newRoot->left;
        newRoot->left = root;
        return newRoot;
    }

    NodeTR* findTreap(NodeTR* root, string key) {
        if (root == nullptr || root->key == key) // Retorna o nó se a chave for encontrada ou se a árvore estiver vazia
            return root;  
        if (key < root->key)  
            return findTreap(root->left, key); // Busca na subárvore esquerda se a chave for menor que a chave do nó atual
        else 
            return findTreap(root->right, key); // Busca na subárvore direita se a chave for maior que a chave do nó atual
    }


    /*================================================VETOR ORDENADO===================================================*/

    void AddVO(vector<NodeVO>& nodeVector, string key, Item value) {
        int low = 0;
        int high = nodeVector.size() - 1;

        while (low <= high) {  // Encontra o índice do meio do vetor
            int mid = (low + high) / 2;
            if (key < nodeVector[mid].key) 
                high = mid - 1;
            else if (key > nodeVector[mid].key)
                low = mid + 1;
            else { // Se a chave já existe no vetor, atualiza o valor e incrementa a ocorrência
                nodeVector[mid].value = value;
                nodeVector[mid].value.ocorrencia++;
                return;
            }
        }
        NodeVO newNode(key, value); // Cria um novo nó com a chave e valor fornecidos
        newNode.value.ocorrencia++;
        nodeVector.insert(nodeVector.begin() + low, newNode); // Insere o novo nó no vetor na posição correta
    }

    int findVO(const vector<NodeVO>& nodeVector, string key, int low, int high) {
        if (low > high)
            return -1;
        int mid = (low + high) / 2;
        if (nodeVector[mid].key == key)
            return mid; 
        else if (key < nodeVector[mid].key) // Realiza uma busca binária recursiva na metade inferior do vetor 
            return findVO(nodeVector, key, low, mid - 1);
        else // Realiza uma busca binária recursiva na metade superior do vetor
            return findVO(nodeVector, key, mid + 1, high);
    }

public:

    SymbolTable() {
        // Inicializa os ponteiros das estruturas como nullptr
        rootABB = nullptr;
        rootARN = nullptr;
        rootA23 = nullptr;
        rootTR = nullptr;
    }

    string estrutura;

    void add(string key, Item value) {
        // Verifica qual é a estrutura atualmente selecionada
        if (estrutura == "ABB")
            // Chama a função addABB para adicionar o nó na Árvore Binária de Busca
            rootABB = addABB(rootABB, key, value);
        else if (estrutura == "ARN")
            // Chama a função addARN para adicionar o nó na Árvore Rubro-Negra
            rootARN = addARN(rootARN, key, value);
        else if (estrutura == "A23"){
            // Chama a função addA23 para adicionar o nó na Árvore 2-3
            rootA23 = addA23(rootA23, key, value);
        }   
        else if (estrutura == "TR"){
            // Chama a função AddTreap para adicionar o nó na Treap
            rootTR = AddTreap(rootTR, key, value);
        }
        else if (estrutura == "VO"){
            // Chama a função AddVO para adicionar o nó no vetor ordenado
            AddVO(nodeVector, key, value);
        }
    }
    

    Item value(string key) {
        // Verifica qual é a estrutura atualmente selecionada

        if (estrutura == "ABB"){
            // Encontra o nó correspondente à chave na Árvore Binária de Busca
            NodeABB* NodeABB = findABB(rootABB, key);
            if (NodeABB != nullptr) 
                return NodeABB->value;
        }
        else if (estrutura == "ARN") {
            // Encontra o nó correspondente à chave na Árvore Rubro-Negra
            NodeARN* nodeARN = findARN(rootARN, key);
            if (nodeARN != nullptr) 
                return nodeARN->value;
        }
        else if (estrutura == "A23") {
            // Encontra o nó correspondente à chave na Árvore 2-3
            NodeA23* nodeA23 = findA23(rootA23, key);
            if (nodeA23 != nullptr){
                // Verifica se a chave é igual à key1 do nó
                if (key == nodeA23->key1)
                    return nodeA23->value1;
                // Verifica se a chave é igual à key2 do nó
                else if (key == nodeA23->key2)
                    return nodeA23->value2;
            }
        }
        else if (estrutura == "TR"){
            // Encontra o nó correspondente à chave na Treap
            NodeTR* NodeTR = findTreap(rootTR, key);
            if (NodeTR != nullptr) 
                return NodeTR->value;
        }
        else if (estrutura == "VO"){
            // Encontra a posição da chave no vetor ordenado
            int posicao = findVO(nodeVector, key, 0, nodeVector.size() - 1);
            if (posicao != -1) {
                // Retorna o valor do nó no vetor
                return nodeVector[posicao].value;
            }
        }

        // Se nenhum nó correspondente à chave for encontrado, retorna um Item vazio
        Item emptyItem;
        emptyItem.ocorrencia = 0;
        emptyItem.numLetters = 0;
        emptyItem.numUniqueVowels = 0;
        return emptyItem;
    }
};

bool isVowel(char c) {
    // Converte o caractere para minúsculo
    c = tolower(c);
    // Verifica se o caractere é uma vogal
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int countUniqueVowels(string word) {
    // Cria um conjunto para armazenar as vogais únicas
    unordered_set<char> vowels;
    // Percorre cada caractere da palavra
    for (char c : word) {
        // Verifica se o caractere é uma vogal
        if (isVowel(c)) {
            // Insere a vogal no conjunto
            vowels.insert(c);
        }
    }
    // Retorna o tamanho do conjunto, ou seja, a quantidade de vogais únicas encontradas
    return vowels.size();
}

void consultas() {
    // Cria uma instância da SymbolTable
    SymbolTable symbolTable;
    // Define o nome do arquivo de entrada
    string filename = "input.txt";
    // Abre o arquivo
    ifstream inputFile(filename);

    if (!inputFile) {
        // Exibe uma mensagem de erro caso haja falha ao abrir o arquivo
        cerr << "Falha ao abrir o arquivo: " << filename << endl;
        return;
    }

    string estrutura;
    // Lê a estrutura selecionada do arquivo
    inputFile >> estrutura;
    // Atribui a estrutura selecionada à variável estrutura da SymbolTable
    symbolTable.estrutura = estrutura;

    int numWords, numQueries;;
    int MaisFrequente, maxNumLetters, maxWordLength, maxUniqueVowelsCount = 0;
    int minNumLettersWithUniqueVowels = INT_MAX;

    unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
    vector<string> wordMaisFrequnte;
    unordered_set<string> uniqueWordsWithMaxNumLetters;
    unordered_set<string> uniqueWordsWithMaxUniqueVowels;
    unordered_set<string> uniqueWordsWithoutRepetition;

    inputFile >> numWords;

    string word;
    // Loop para ler as palavras do arquivo e processá-las
    for (int i = 0; i < numWords; i++) {
        Item item;
        inputFile >> word;
        // Obtém o item correspondente à palavra da SymbolTable
        item.ocorrencia = symbolTable.value(word).ocorrencia;
        item.numLetters = word.size();
        item.numUniqueVowels = countUniqueVowels(word);
        // Adiciona a palavra e o item correspondente na SymbolTable
        symbolTable.add(word, item);

        /*ACHAR A PALAVRA MAIS FREQUENTE*/
        if (symbolTable.value(word).ocorrencia > MaisFrequente) {
            MaisFrequente = symbolTable.value(word).ocorrencia;
            wordMaisFrequnte.clear();
            wordMaisFrequnte.push_back(word);
        } else if (symbolTable.value(word).ocorrencia == MaisFrequente) 
            wordMaisFrequnte.push_back(word);
    
        /*ACHAR PALAVRA COM MAIOR NUMERO DE LETRAS*/
        if (item.numLetters > maxNumLetters) {
            maxNumLetters = item.numLetters;
            uniqueWordsWithMaxNumLetters.clear();
            uniqueWordsWithMaxNumLetters.insert(word);
        } else if (item.numLetters == maxNumLetters) 
            uniqueWordsWithMaxNumLetters.insert(word);
    
        /*ACHAR A MENOR PALAVRA COM MENOS VOGAIS SEM REPETIÇÃO*/
        if (item.numUniqueVowels > maxUniqueVowelsCount) {
            uniqueWordsWithMaxUniqueVowels.clear();
            uniqueWordsWithMaxUniqueVowels.insert(word);
            maxUniqueVowelsCount = item.numUniqueVowels;
            minNumLettersWithUniqueVowels = item.numLetters;
        } else if (item.numUniqueVowels == maxUniqueVowelsCount && item.numLetters < minNumLettersWithUniqueVowels) {
            uniqueWordsWithMaxUniqueVowels.clear();
            uniqueWordsWithMaxUniqueVowels.insert(word);
            minNumLettersWithUniqueVowels = item.numLetters;
        } else if (item.numUniqueVowels == maxUniqueVowelsCount && item.numLetters == minNumLettersWithUniqueVowels) 
            uniqueWordsWithMaxUniqueVowels.insert(word);

        /*ACHAR A MAIOR PALAVRA QUE NÃO REPETE LETRAS*/
        bool hasRepetition = false;
        unordered_set<char> uniqueChars;

        for (char c : word) {
            c = tolower(c);
            // Verifica se o caractere já foi encontrado anteriormente
            if (uniqueChars.find(c) != uniqueChars.end()) {
                hasRepetition = true;
                break;
            }
            // Insere o caractere no conjunto de caracteres únicos
            uniqueChars.insert(c);
        }

        if (!hasRepetition && item.numLetters > maxWordLength) {
            uniqueWordsWithoutRepetition.clear();
            uniqueWordsWithoutRepetition.insert(word);
            maxWordLength = item.numLetters;
        } else if (!hasRepetition && item.numLetters == maxWordLength) 
            uniqueWordsWithoutRepetition.insert(word);
    }

    inputFile >> numQueries;
    string Query;
    cout << endl;
    // Loop para ler as consultas do arquivo e realizar as ações correspondentes
    for (int i = 0; i < numQueries; i++) {
        inputFile >> Query;
        Item result;

        if (Query == "O") {
            inputFile >> word;
            // Obtém o resultado da consulta para a palavra especificada
            result = symbolTable.value(word);
            cout << "A palavra " << word;
            cout << " ocorre " << result.ocorrencia << " vez(es)"<< endl;
        }
        if(Query == "F"){
            cout << "Palavra(s) mais Frequente(s): ";
            // Exibe as palavras mais frequentes
            for (const auto& word : wordMaisFrequnte) 
                cout << "** "<< word << " ** ";
            cout << endl;
        }
        if(Query == "L"){
            cout << "Palavra(s) com maior número de letras: ";
            // Exibe as palavras com maior número de letras
            for (const auto& uniqueWord : uniqueWordsWithMaxNumLetters) 
                cout << uniqueWord << " ";
            cout << endl;
        }
        if(Query =="SR"){
            if (!uniqueWordsWithoutRepetition.empty()) {
                cout << "A(s) maiore(s) palavra(s) sem letra(s) repetida(s) é (são): ";
                // Exibe as palavras sem repetição de letras
                for (const string& word : uniqueWordsWithoutRepetition) {
                    cout << word << " ";
                }
                cout << endl;
            } else 
                cout << "Nenhuma palavra sem letras repetidas encontrada." << endl;       
        }
        if(Query == "VD"){
            if (!uniqueWordsWithMaxUniqueVowels.empty()) {
                    cout << "A(s) menor palavra(s) com mais vogais sem repetição é: ";
                    // Exibe as palavras com maior número de vogais únicas
                    for (const string& word : uniqueWordsWithMaxUniqueVowels) {
                        cout << word << " ";
                    }
                    cout << endl;
                } else 
                    cout << "Nenhuma palavra com vogais sem repetição encontrada." << endl;  
        }
    }
    // Fecha o arquivo
    inputFile.close();
}


int main() {

    auto start = chrono::high_resolution_clock::now();
    consultas();
    auto end = std::chrono::high_resolution_clock::now();

    // Calcula a duração em segundos
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Exibe o tempo de execução em segundos com 6 casas decimais
    double durationInSeconds = static_cast<double>(duration) / 1000.0;
    printf("\nTempo de execução: %.6f segundos\n\n", durationInSeconds);

    return 0;
    
}