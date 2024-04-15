#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <stack>
using namespace std;
#define fita_original ""


pair<vector<vector<int>>, vector<vector<int>>> criarGrafo(const vector<string>& vertices, int K) {
    int numVertices = vertices.size();
    vector<vector<int>> grafo(numVertices, vector<int>(numVertices, 0));
    vector<vector<int>> grafo_k(numVertices, vector<int>(numVertices, 0));
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (i == j) {
                continue;  // Não há arco de um vértice para ele mesmo
            }

            const string& u = vertices[i];
            const string& v = vertices[j];

            int uLen = u.size();
            int vLen = v.size();
            int k = 0;
            for (int p = 0; p < uLen; p++){
                if (u[p] == v[k])
                    k++;
                else{
                    k=0;
                    if (u[p] == v[k])
                    k++;
                }
            }

            if (k >= K) {
                grafo[i][j] = 1;  // Há um arco entre u e v
                grafo_k[i][j] = k;
            }
        }
    }
    return make_pair(grafo, grafo_k);
}

void maiorCaminho(int currentNode, const vector<vector<int>>& grafo, vector<bool>& visitado, vector<int>& caminho, vector<int>& caminhoMaisLongo) {
    visitado[currentNode] = true;
    caminho.push_back(currentNode);

    bool allvisitado = true;
    for (int i = 0; i < grafo.size(); i++) {
        if (grafo[currentNode][i] == 1 && !visitado[i]) {
            allvisitado = false;
            maiorCaminho(i, grafo, visitado, caminho, caminhoMaisLongo);
        }
    }

    if (allvisitado) {
        if (caminho.size() > caminhoMaisLongo
        .size()) {
            caminhoMaisLongo
             = caminho;
        }
    }

    visitado[currentNode] = false;
    caminho.pop_back();
}

// Função principal para encontrar o maior caminho em um grafo representado por matriz de adjacência
vector<int> procuraCaminhoMaisLongo (const vector<vector<int>>& grafo) {
    vector<int> caminhoMaisLongo
    ;
    vector<bool> visitado(grafo.size(), false);
    vector<int> path;

    for (int i = 0; i < grafo.size(); i++) {
        maiorCaminho(i, grafo, visitado, path, caminhoMaisLongo
        );
    }
    return caminhoMaisLongo;
}

string concatenar(const string& str1, const string& str2) {
    return str1.substr(0, str1.length() - 1) + str2;
}

double calcularErro(const string& fitaOriginal, const string& fitaReconstruida) {
    int ponto = 0;
    int tamanho_reconstruida = fitaReconstruida.length();
    int tamanho_original = fitaOriginal.length();
    int maxs = max(tamanho_original, tamanho_reconstruida);
    vector<int> pontos;
    for (int i = 0; i < tamanho_original; i++) {
        for (int j = 0; j < tamanho_reconstruida; j++){
            if (fitaOriginal[i] == fitaReconstruida[j]) {
                for (int k = 0; j < tamanho_original; k++){
                    ponto++;
                    if (fitaOriginal[k+i] != fitaReconstruida[k+j]){
                        pontos.push_back(ponto);
                        ponto = 0;
                        break;
                    }
                }
            }
        }
    }

    int tamanho = pontos.size();
    int maior = pontos[0]; // Supomos que o primeiro elemento é o maior
    for (int i = 1; i < tamanho; i++) {
        if (pontos[i] > maior) {
            maior = pontos[i];
        }
    }
    double erro = (1 - static_cast<double>(maior)/static_cast<double>(maxs))*100; /*diferença entre o maior trecho em comum e o tamanho máximo entre as sequências, normalizado para um valor entre 0% e 100%.  */
    return erro;
}

int main() {

    ifstream inputFile("arquivo.txt");  // Nome do arquivo a ser lido

    if (!inputFile.is_open()) {
        cout << "Não foi possível abrir o arquivo." << endl;
        return 1;
    }

    int numVertices;
    inputFile >> numVertices;  // Lê o número de vértices

    vector<string> vertices;

    string vertex;
    while (inputFile >> vertex) {  // Lê cada vértice
        vertices.push_back(vertex);
    }

    inputFile.close();


    int K;
    cout << endl;
    cout << "Digite o valor de K: ";
    scanf("%d", &K);
    vector<vector<int>> grafo;
    vector<vector<int>> grafo_k;
    tie(grafo, grafo_k) = criarGrafo(vertices, K);

    // Exibindo a matriz do grafo
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            cout << grafo[i][j] << " ";
        }
        cout << endl;
    }

    vector<int> caminhoMaisLongo = procuraCaminhoMaisLongo(grafo);

    cout << endl << "Maior caminho possível: ";
        for (int i = 0; i < caminhoMaisLongo.size(); i++) {
            cout << caminhoMaisLongo[i];
            if (i != caminhoMaisLongo.size() - 1) {
                cout << " - ";
            }
        }
        if (fita_original != "")
            cout << endl << "Fita Original: " << fita_original;
        string fita_reconstruida = vertices[caminhoMaisLongo[0]];
        string aux;
        for(int i = 0; i < caminhoMaisLongo.size() - 1; i++){
            aux = vertices[caminhoMaisLongo[i+1]].substr(grafo_k[caminhoMaisLongo[i]][caminhoMaisLongo[i+1]]);
            fita_reconstruida = fita_reconstruida + aux;              
        }

        cout << endl << "Fita Reconstruída: " << fita_reconstruida << endl;

        if (fita_original != ""){
            double erro = calcularErro(fita_original, fita_reconstruida);
            cout << "Semelhaça: " << 100-erro <<"%"<< endl;    
            cout << "Erro: " << erro <<"%"<< endl << endl;
        }
        return 0;    
}