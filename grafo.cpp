//AJUSTAR NUMERO N DA LEITURA QUE PEGA SOMENTE UM DIGITO DE INTEIRO

#include <iostream>
#include <fstream>
#include <stdlib.h>

//#define DEBP // DEBug Print

using namespace std;

void lerArquivo();
void pegarVertices(string s, int i);
void pegarArestas(string s, int i, int x);
char mostrarMenu();
void mostrarVizinhos();
void sequenciaDeGraus();
bool dijkstra();
void criarTabela(int m[][4], int i);
void atualizarTabela(int m[][4], int i, int l, int k, int &atual);
bool verificarVizinhos(int l, int lim);
int pegarVMenorCusto(int m[][4], int i);
bool verificarPartidas(int i, int lim);
void atualizarCusto(int iAtual, int i, int m[][4]);
//void mostrarTudo();

string L1[50];
string L2[50];
string L3[50];
string L4[50];
int L5[50];

int main(){

    char r = 'Z';

    while(r != 'E' || r != 'e'){

        r = mostrarMenu();

        if(r == 'R' || r == 'r'){
            lerArquivo();
            //mostrarTudo();
        }else if(r == 'N' || r == 'n'){
            mostrarVizinhos();
        }else if(r == 'S' || r == 's'){
            sequenciaDeGraus();
        }else if(r == 'D' || r == 'd'){
            dijkstra();
        }else if(r == 'E' || r == 'e'){
            break;
        }else{
            cout << "Invalid command!" << endl;
            cout << endl;
        }
    }
}

#ifdef DEBP
void mostrarTudo(){
    for(int i = 0; i < 5; i++){
        cout << L1[i] << " ";
    }

    cout << endl;
    cout << endl;

    for(int i = 0; i < 7; i++){
        cout << L2[i] << " ";
    }

    cout << endl;

    for(int i = 0; i < 7; i++){
        cout << L3[i] << " ";
    }

    cout << endl;

    for(int i = 0; i < 7; i++){
        cout << L4[i] << " ";
    }

    cout << endl;

    for(int i = 0; i < 7; i++){
        cout << L5[i] << " ";
    }

    cout << endl;
}
#endif

void lerArquivo(){
    ifstream arq;
    arq.open("file.txt");

    if(!arq){
        cout << "Could not open the file!" << endl;
    }else{
        string s;
        int a = 2;

        while(a--){
            arq >> s;
            int n = atoi(s.c_str());
            int xVert = 0;
            int xArest = 0;

            if(a == 1){
                while(n--){
                    arq >> s;

                    pegarVertices(s, xVert);
                    xVert++;
                }
            }else{
                int i = 0;
                while(arq >> s){

                    pegarArestas(s, i, xArest);

                    i++;
                    if(i == 4){
                        i = 0;
                        xArest++;
                    }
                }
            }
        }
    }

    cout << endl;
    cout << "File read successfully!" << endl;
    cout << endl;
}

void pegarVertices(string s, int i){
    L1[i] = s;
}

void pegarArestas(string s, int i, int x){

    if(i == 0){
        L2[x] = s;
    }else if(i == 1){
        L3[x] = s;
    }else if(i == 2){
        L4[x] = s;
    }else if(i == 3){
        int valor = atoi(s.c_str());
        L5[x] = valor;
    }
}

char mostrarMenu(){
    char r;

    cout << "***************OPTIONS****************" << endl;
    cout << endl;
    cout << "[R] - READING" << endl;
    cout << "[N] - NEIGHBORHOOD" << endl;
    cout << "[S] - DEGREE SEQUENCE" << endl;
    cout << "[D] - DIJKSTRA" << endl;
    cout << "[E] - EXIT" << endl;
    cout << endl;

    cout << "Enter the desired option: ";
    cin >> r;

    return r;
}


void mostrarVizinhos(){
    string rotulo;
    bool flag = false;

    cout << "Enter the vertex label (example: V01): ";
    cin >> rotulo;

    cout << endl;
    cout << "Vertex neighbors: " << rotulo << ": ";
    cout << endl;

    for(int i = 0; i < 50; i++){
        if(L3[i] == rotulo){
            flag = true;
            cout << L4[i] << "\t";
        }
    }

    if(flag == false){
        cout << "The vertex has no neighbors." << endl;
    }

    cout << endl;
    cout << endl;
}

void sequenciaDeGraus(){

    cout << "Degree sequence = VERTEX(DEGREE): " << endl;

    for(int i = 0; i < 50; i++){
        int c = 0;

        if(L1[i] == "\0"){
            break;
        }

        for(int j = 0; j < 50; j++){

            if(L3[j] == "\0"){
                break;
            }

            if(L3[j] == L1[i]){
                c++;
            }
        }
        cout << L1[i] << "(" << c << ")" << "\t";
    }

    cout << endl;
    cout << endl;
}

bool dijkstra(){
    string vO, vD;
    int atual = -1;
    int iO = -1;
    int iD = -1;

    int i = 0;
    while(L1[i] != "\0"){
        i++;
    }

    int y = 0;
    while(L2[y] != "\0"){
        y++;
    }

    int m[i][4];

    cout << "Origin Vertex: ";
    cin >> vO;
    cout << "Target Vertex: ";
    cin >> vD;

    criarTabela(m, i);

    for(int j = 0; j < i; j++){
        if(L1[j] == vO){
            iO = j;
        }

        if(L1[j] == vD){
            iD = j;
        }
    }

    //caso for digitado um vertice que nao existe
    if(iO == -1){
        cout << "The origin vertex does not exist!" << endl;
        return false;
    }else if(iD == -1){
        cout << "Destination vertex does not exist!" << endl;
        return false;
    }

    m[iO][2] = 0; //zera o origem
    cout << m[iO][2] << m[iO][0] << endl;

    while(true){
        int vMenorCusto = pegarVMenorCusto(m, i);
        if(verificarPartidas(vMenorCusto, y) == false){
            cout << "There is no path between these two vertices!" << endl; cout << endl;
            break;
        }

        atual = vMenorCusto;
        m[atual][0] = 1; //fecha o atual

        if(atual == iD){
            cout << "FIND THE WAY!" << endl;
            break;
        }

        //atualizarCusto(atual, i, m);
/*
        for(int k = 0; k < i; k++){
            cout << m[k][0] << '\t' << L1[m[k][1]] << '\t' << m[k][2] << '\t' << m[k][3] << endl;
        }*/
    }
}

void criarTabela(int m[][4], int i){

    for(int j = 0; j < i; j++){
        for(int k = 0; k < 4; k++){
            if(k == 0){
                m[j][k] = 0; //0 = S, 1 = N
            }else if(k == 1){
                m[j][k] = j; //somente o indice do vetor L1
            }else if(k == 2){
                m[j][k] = 9999;
            }else if(k == 3){
                m[j][k] = -1;
            }
        }
    }
}

void atualizarCusto(int iAtual, int i, int m[][4]){

    for(int j = 0; j < i; j++){
        if(L3[j] == L1[iAtual]){
            m[j][0] = 1;
            if(m[j][2] > m[iAtual][2] + L5[j]){
                m[j][2] = m[iAtual][2] + L5[j];
                m[j][3] = iAtual;
            }
        }
    }
}

int pegarVMenorCusto(int m[][4], int i){
    int menor = 9999;

    for(int j = 0; j < i; j++){
        cout << m[j][0] << m[j][1] << m[j][2] << m[j][3] << endl;
        if(m[j][2] < menor && m[j][0] == 0){
            menor = m[j][2];
            return j;
        }
    }

    return -1;
}

bool verificarPartidas(int i, int lim){
    for(int j = 0; j < lim; j++){
        if(L3[j] == L1[i]){
            return true;
        }
    }

    return false;
}
