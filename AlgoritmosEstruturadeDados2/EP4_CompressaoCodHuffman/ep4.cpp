#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node {
    char character;
    int frequency;
    Node* left;
    Node* right;
};

struct CompareNodes {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};

unordered_map<char, int> getCharacterFrequencies(const string& text) {
    unordered_map<char, int> frequencies;
    for (char ch : text) {
        frequencies[ch]++;
    }
    return frequencies;
}

Node* buildHuffmanTree(const unordered_map<char, int>& frequencies) {
    priority_queue<Node*, vector<Node*>, CompareNodes> minHeap;

    for (const auto& pair : frequencies) {
        Node* newNode = new Node;
        newNode->character = pair.first;
        newNode->frequency = pair.second;
        newNode->left = nullptr;
        newNode->right = nullptr;
        minHeap.push(newNode);
    }

    while (minHeap.size() > 1) {
        Node* x = minHeap.top();
        minHeap.pop();
        Node* y = minHeap.top();
        minHeap.pop();

        Node* newNode = new Node;
        newNode->character = '\0';
        newNode->frequency = x->frequency + y->frequency;
        newNode->left = x;
        newNode->right = y;
        minHeap.push(newNode);
    }

    return minHeap.top();
}

void traverseHuffmanTree(Node* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    if (root->character != '\0') {
        huffmanCodes[root->character] = code;
    }

    traverseHuffmanTree(root->left, code + '0', huffmanCodes);
    traverseHuffmanTree(root->right, code + '1', huffmanCodes);
}

unordered_map<char, string> getHuffmanCodes(Node* root) {
    unordered_map<char, string> huffmanCodes;
    traverseHuffmanTree(root, "", huffmanCodes);
    return huffmanCodes;
}

string encodeText(const string& text, const unordered_map<char, string>& huffmanCodes) {
    string bin;
    for (char ch : text) {
        bin += huffmanCodes.at(ch);
    }
    return bin;
}

void decodeText(const string& encodedText, Node* root) {

    ofstream file("descompactado.txt");
    if (!file.is_open()){
        cerr << "Nao foi possivel abrir o arquivo para escrita." << endl;
        return;
    }
    
    Node* current = root;

    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (current->left == nullptr && current->right == nullptr) {
            //cout << current->character;
            file << current->character;
            current = root;
        }
    }
    cout << endl << "Texto foi descompactado com Sucesso e salvo no arquivo descompactado.txt" << endl << endl;
}

void textToBinaryFile(const string& binaryText, const string& fileName) {
    ofstream outputFile(fileName, ios::binary);
    if (!outputFile.is_open()) {
        cout << "Erro ao abrir o arquivo para escrita." << endl;
        return;
    }

    string byte;
    for (size_t i = 0; i < binaryText.length(); i += 8) {
        byte = binaryText.substr(i, 8);
        char character = static_cast<char>(stoi(byte, nullptr, 2));
        outputFile.write(&character, sizeof(character));
    }

    outputFile.close();
    cout << endl << "Texto binario convertido e salvo no arquivo " << fileName << endl;
}

string lerArquivoBinario(const string& nomeArquivoBinario) {
    ifstream arquivoBinario(nomeArquivoBinario, ios::binary);

    if (!arquivoBinario.is_open()) {
        cerr << "Erro ao abrir o arquivo binario." << endl;
        return "";
    }

    string text;
    char byte;

    while (arquivoBinario.read(&byte, sizeof(byte))) {
        for (int i = 7; i >= 0; i--) {
            text += ((byte >> i) & 1) ? '1' : '0';
        }
    }

    arquivoBinario.close();

    return text;
}

int main() {

    string filename;
    cout << endl << "Digite o nome do arquivo que deseja comprimir/descomprimir: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Falha ao abrir o arquivo" << endl;
        return 1;
    }

    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    unordered_map<char, int> frequencies = getCharacterFrequencies(text);
    Node* huffmanTree = buildHuffmanTree(frequencies);
    unordered_map<char, string> huffmanCodes = getHuffmanCodes(huffmanTree);
    string k;
    /*cout << endl << "Huffman Codes:" << endl;
    for (const auto& pair : huffmanCodes) {
       cout << pair.first << ": " << pair.second << endl;
    }*/
    string bin, bin2;
    bin = encodeText(text, huffmanCodes);
    //cout << endl <<"Encoded Text: " << bin << endl;
    textToBinaryFile(bin, "compactado.bin");

    bin2 = lerArquivoBinario("compactado.bin");
    //cout << endl << "Decoded Text: " << endl;
    decodeText(bin2, huffmanTree);

    return 0;
}