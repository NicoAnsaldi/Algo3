#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <sys/stat.h>
#include <iomanip>
#include <time.h>
using namespace std;

int tiempo;

random_device rd;
mt19937 generator(rd());
string msg, color, oponent_color, go_first;
int columns, rows, c, p, col;
int movimiento = 0;
int maxCont = 0;
int maxMio = 0;
vector<int> cuadrantes;
vector<int> columnass;
int posicionesDisponibles;


void send(const string& msg) {
    cout << msg << endl;
}

void send(int msg) {
    cout << msg << endl;
}

int read_int() {
    string msg;
    cin >> msg;
    if (msg == "salir") {
        send("listo");
        exit(0);
    }
    return stoi(msg);
}

string read_str() {
    string msg;
    cin >> msg;
    if (msg == "salir") {
        send("listo");
        exit(0);
    }
    return msg;
}

int min(int a , int b){
    if(a<b){
        return a;
    }
    return b;
}

int max(int a , int b){
    if(a>b){
        return a;
    }
    return b;
}


int dondeEstoy( int col, int fila ){
    if(col < columns/2 && fila < rows/2) return 0;
    if(col < columns/2 && fila >= rows/2) return 1;
    if(col >= columns/2 && fila >= rows/2) return 2;
    if(col >= columns/2 && fila < rows/2) return 3;
}


int disponible(vector< vector<int> >& matri, vector<int> primDisp, int col, int fila, int jugador){
    if (primDisp[col] == fila || matri[fila][col] == jugador){
        return 1;
    }
    return 0;
}

int disponiblePonderado(vector< vector<int> >& matri, vector<int> primDisp, int col, int fila, int jugador){
    if (primDisp[col] == fila && matri[fila][col] == -1){
        return 1;
    }
    return 0;
}


int horizontalLibre(vector< vector<int> >& matri, vector<int> primDisp, int col, int fila, int jugador){
    int res = 1;
    if(col > 0 && disponible(matri,primDisp,col-1,fila,jugador)){
    res++;
    }
    if(col > 1 && disponible(matri,primDisp,col-2,fila,jugador)){
    res++;
    }
    if(col < columns-1 && disponible(matri,primDisp,col+1,fila,jugador)){
    res++;
    }
    if(col < columns-2 && disponible(matri,primDisp,col+2,fila,jugador)){
    res++;
    }
    if (res >= c) return 1;
    return 0;
}


int nuevoValor(vector< vector<int> >& matri,  int col, int fila, int jugador){ 
    int diagizq = 1; // diagonalizqarriba, diagonalderarriba, vertical, horizontal
    int diagder = 1;
    int abajo = 1;
    int horiz = 1;
    int colaux = col;
    int filaaux = fila;
    int res = 0;

    while(filaaux > 0 && (matri[filaaux-1][colaux]) == jugador){
        abajo++;
        filaaux--;
    }
    colaux = col;
    filaaux = fila;

    while(colaux > 0 && (matri[filaaux][colaux-1]) == jugador){
        horiz++;
        colaux--;
    }
    colaux = col;
    filaaux = fila;

    while(colaux < columns-1 && (matri[filaaux][colaux+1]) == jugador){
        horiz++;
        colaux++;
    }
    colaux = col;
    filaaux = fila;

    while(filaaux > 0 && colaux > 0 && (matri[filaaux-1][colaux-1]) == jugador){
        diagder++;
        colaux--;
        filaaux--;
    }
    colaux = col;
    filaaux = fila;

    while(filaaux < rows-1 && colaux < columns-1 && (matri[filaaux+1][colaux+1]) == jugador){
        diagder++;
        colaux++;
        filaaux++;
    }
    colaux = col;
    filaaux = fila;

    while(filaaux > 0 && colaux < columns-1 && (matri[filaaux-1][colaux+1]) == jugador){
        diagizq++;
        colaux++;
        filaaux--;
    }
    colaux = col;
    filaaux = fila;

    while(filaaux < rows-1 && colaux > 0 && (matri[filaaux+1][colaux-1]) == jugador){
        diagizq++;
        colaux--;
        filaaux++;
    }

    res = max(diagder,diagizq);
    res = max(res, abajo);
    res = max(res, horiz);

    return res;
}

int nuevoValorGen(vector< vector<int> >& matri,  int col, int fila, int jugador, vector< int> pesosPrioridad, vector<int> primDisp){ 
    int diagizq;
    int diagder;
    int abajo;
    int horiz;

    diagizq = pesosPrioridad[0]; // diagonalizqarriba, diagonalderarriba, vertical, horizontal
    diagder = pesosPrioridad[1];
    abajo = pesosPrioridad[2];
    horiz = pesosPrioridad[3];

    int colaux = col;
    int filaaux = fila;
    int res = 0;

    /*if (horizontalLibre( matri, primDisp, col, fila, jugador)){
        horiz = abs(horiz) + 100;
    }*/


    while(filaaux > 0 && (matri[filaaux-1][colaux]) == jugador){
        abajo+=abajo;
        filaaux--;
    }
    colaux = col;
    filaaux = fila;

    while(colaux > 0 && (matri[filaaux][colaux-1]) == jugador){
        horiz+= horiz;
        colaux--;
    }
    colaux = col;
    filaaux = fila;

    while(colaux < columns-1 && (matri[filaaux][colaux+1]) == jugador){
        horiz+= horiz;
        colaux++;
    }
    colaux = col;
    filaaux = fila;

    while(filaaux > 0 && colaux > 0 && (matri[filaaux-1][colaux-1]) == jugador){
        diagder+= diagder;
        colaux--;
        filaaux--;
    }
    colaux = col;
    filaaux = fila;

    while(filaaux < rows-1 && colaux < columns-1 && (matri[filaaux+1][colaux+1]) == jugador){
        diagder+= diagder;
        colaux++;
        filaaux++;
    }
    colaux = col;
    filaaux = fila;

    while(filaaux > 0 && colaux < columns-1 && (matri[filaaux-1][colaux+1]) == jugador){
        diagizq+=diagizq;
        colaux++;
        filaaux--;
    }
    colaux = col;
    filaaux = fila;

    while(filaaux < rows-1 && colaux > 0 && (matri[filaaux+1][colaux-1]) == jugador){
        diagizq+=diagizq;
        colaux--;
        filaaux++;
    }

    res = max(diagder,diagizq);
    res = max(res, abajo);
    res = max(res, horiz);

    int i;
    i = dondeEstoy(col, fila);

    //if (rand() % 10 > 4){
        res = res + cuadrantes[i];
    //}
    
    if (rand() % 10 > 8){
        res = res + columnass[col];
    }

    return res;
}

int fichaGanadora(vector< vector<int> >& matri, vector<int> primDisp,int jugador){ // o(n)
int aux;
    int i = 0;
    while (i < columns){
        aux = primDisp[i];
        if (aux < rows){
            int pepe = nuevoValor(matri, i, primDisp[i], jugador);
            if ( pepe >= c){ // va de 0 a c
                return i;
            }
        }
    i++;
    }
    return -1;
}

int greedy( vector< vector<int> >& matri, int jugador, vector<int> primDisp, vector<int>& pesosPrioridad){

    int actual;
    int res;
    int max = -1000;
    int i = 0;
    int aux;

    int aux2 = fichaGanadora(matri, primDisp, 1); // o(columnas)
    if (aux2 != -1){
        return aux2;
    }

    aux2 = fichaGanadora(matri, primDisp, 0); // o(columnas)
    if (aux2 != -1){
        return aux2;
    }

    while(i < columns ){ //  o(columnas)
        aux = primDisp[i];
        if (aux < rows){

            actual = nuevoValorGen(matri, i, aux, jugador, pesosPrioridad, primDisp); //o(1)
            if (actual > max){
                max = actual;
                res = i;
            }
        }
    i++;
    }
    return res;
}

int main() {

    srand(time(NULL));
    ofstream output;
    output.open ("output2.txt");
    ifstream input;
    input.open("pesosFijos.txt");

    while (true) {
        color = read_str();
        oponent_color = read_str();
        columns = read_int();
        rows = read_int();
        c = read_int();
        p = read_int();
        posicionesDisponibles = columns*rows;

        vector< vector<int> > matri;
        for(int i = 0; i < rows;i++){
            vector<int> cosopo;
            matri.push_back(cosopo);
            for(int j = 0; j < columns;j++){
                matri[i].push_back(-1);
            }
        }
        // PARAMETROS ------------------------------------------------------------------------------------------------------  
        vector<int> pesosPrioridad;
        int z = 0;
        while(z < 4){ // diagonalizqarriba, diagonalderarriba, vertical, horizontal
            pesosPrioridad.push_back(1);
            z++;
        }
        z = 0;
        while(z < 4){ // diagonalizqarriba, diagonalderarriba, vertical, horizontal
            input >> pesosPrioridad[z];
            z++;
        }

        //CUADRANTES
        
        z = 0;
        while(z < 4){ // izq abajo, izq arriba, der arriba, der abajo
            cuadrantes.push_back(1);
            input >> cuadrantes[z];
            z++;
        }

        //columnas
        z = 0;
        while(z < columns){ // 0,1 ... columns
            columnass.push_back(1);
            z++;
        }

        
            z = 0;
            while(z < columns){ // 0,1 ... columns
                input >> columnass[z];
                z++;
            }
            

        // diagonalizqarriba, diagonalderarriba, vertical, horizontal, izq abajo, izq arriba, der arriba, der abajo, columnas


        //--------------------------------------------------------------------------------------------------------------------
        vector<int> primDisp;
        z = 0;
        while(z < columns){
            primDisp.push_back(0);
            z++;
        }

        go_first = read_str();
        if (go_first == "vos") {

            int res;
            res = greedy( matri, 1, primDisp, pesosPrioridad);
            int aux = primDisp[res];
            matri[aux][res] = 1; // O(1)
            primDisp[res]++;
            posicionesDisponibles--;
            send(res);
        }

        while (true) {
            msg = read_str();
            if (msg == "ganaste" || msg == "perdiste" || msg == "empataron" || msg=="salir") {
                output << msg << endl;
                break;
            }
            col = stoi(msg);
            int fila = primDisp[col];
            matri[fila][col] = 0; // O(1)
            primDisp[col]++;

            int res;
            res = greedy( matri, 1, primDisp, pesosPrioridad); // o(n)
            int aux = primDisp[res];
            matri[aux][res] = 1; // O(1)
            primDisp[res]++;
            posicionesDisponibles--; 
            send(res);
        }
    }

    input.close();
    output.close();
    return 0;

}


//-20 -26 -53 43 24 17 71 43 -94 -47 22 91 -96 -2 -56
// es un buen peso