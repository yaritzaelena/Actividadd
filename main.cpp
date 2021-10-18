//Irene Garzona Moya - Yaritza Lopez Bustos

#include <string>
#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

struct Node {
    char simbolo;
    int frecuencia;

    Node *izq, *der;
};

Node* getNode(char simbolo, int frecuencia, Node* izq, Node* der){
    Node* nodo = new Node();

    nodo -> simbolo = simbolo;
    nodo -> frecuencia = frecuencia;
    nodo -> izq = izq;
    nodo -> der = der;

    return nodo;
}

struct comp{
    bool operator() (Node* i, Node* d){
        return i -> frecuencia > d->frecuencia;
    }
};

void encode (Node* raiz, string str, unordered_map<char, string> &CodigoHuffman ){
    if (raiz == nullptr)
        return;
    if (!raiz -> izq && !raiz->der){
        CodigoHuffman[raiz -> simbolo] = str;
    }
    encode (raiz ->izq, str + "0", CodigoHuffman);
    encode (raiz ->der, str + "1", CodigoHuffman);

}

void decode (Node* raiz, int &index, string str){
    if (raiz == nullptr){
        return;
    }
    if (!raiz -> izq && !raiz->der){
        cout << raiz ->simbolo;
        return;
    }

    index++;
    if (str[index] == '0')
        decode(raiz->izq, index, str);
    else
        decode (raiz->der, index, str);

}

void CrearArbol (string text){

    unordered_map <char, int> frecuencia;
    for (char simbolo: text){
        frecuencia[simbolo]++;
    }

    priority_queue<Node*, vector<Node*>, comp> pq;
    for (auto pair: frecuencia){
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }
    while (pq.size() != 1){
        Node *izq = pq.top(); pq.pop();
        Node *der = pq.top(); pq.pop();
        int sum = izq -> frecuencia + der-> frecuencia;
        pq.push(getNode('\0',sum, izq, der));
    }

    Node* raiz = pq.top();
    unordered_map<char, string> CodigoHuffman;
    encode (raiz, "", CodigoHuffman);
    cout << "\n Los codigos de HUffman son: \n" << "\n";
    for (auto pair: CodigoHuffman){
        cout << pair.first << " " << pair.second << "\n";

    }

    cout <<"\n Mensaje original: \n" << text << "\n";
    string str = "";
    for (char simbolo: text){
        str += CodigoHuffman[simbolo];
    }
    cout << "\n Codificacion: \n" << str << "\n";
    int index = -1;
    cout << "\n Decodificacion \n";
    while (index < (int) str.size() -2){
        decode(raiz, index, str);
    }
    cout << "\n\n\n";
}

int main() {
    string text;
    cout<< "\n Ingrese el mensaje que desea comprimir: ";
    getline(cin, text);
    CrearArbol(text);
    cout << "\n";
    return 0;

}
