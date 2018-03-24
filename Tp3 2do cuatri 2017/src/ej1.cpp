#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <chrono>
#include <sys/stat.h>
using namespace std;
using namespace std::chrono;

random_device rd;
mt19937 generator(rd());
string msg, color, oponent_color, go_first;
int columns, rows, c, p, col;
int maxCont = 0;
int maxMio = 0;

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

void puntosNuevaFicha(int fila, int col, int& maxAcum, int** board, int parametro){ 
    int diagiz =1;
    int vertical =1;
    int horizontal =1;
    int diagder =1;
    int filaux = fila;
    int colaux = col;
    int maxis;
  while(filaux > 0 && colaux > 0 && board[filaux-1][colaux-1] == parametro){
        diagder++; // suma todas las fichas en la diagonal derecha de abajo
        filaux--;
        colaux--;
    }
    filaux = fila;
    colaux = col;
    while(filaux < rows-1 && colaux < columns-1 && board[filaux+1][colaux+1] == parametro){
        diagder++; // suma todas las fichas en la diagonal derecha de arriba
        filaux++;
        colaux++;
    }
    filaux = fila;
    colaux = col;
    while(filaux > 0 && colaux < columns-1 && board[filaux-1][colaux+1] == parametro){
        diagiz++; // suma todas las fichas en la diagonal izquierda de arriba
        filaux--;
        colaux++;
    }
    filaux = fila;
    colaux = col;
    while(filaux < rows-1 && colaux > 0 &&  board[filaux+1][colaux-1] == parametro){
        diagiz++; // suma todas las fichas en la diagonal izquierda de abajo
        filaux++;
        colaux--;
    }
    filaux = fila;
    colaux = col;
    while(filaux > 0 && board[filaux-1][colaux] == parametro){
        vertical++; // suma las verticales
        filaux--;
    }
    filaux = fila;
    colaux = col;
    while(colaux > 0 && board[filaux][colaux-1] == parametro){
        horizontal++; // suma las que estan a la izquierda
        colaux--;
    }
    filaux = fila;
    colaux = col;
    while(colaux < columns-1 && board[filaux][colaux+1] == parametro){
        horizontal++; // suma las que estan a la derecha
        colaux++;
    }

    maxis = max(diagder,diagiz);
    maxis = max(maxis, vertical);
    maxis = max(maxis, horizontal); // y saca el maximo

    if (maxAcum < maxis) maxAcum = maxis;
}

int minmax(int** board, int fichasRestantes, vector<int>& primDisp, int& posicionesDisp, int alfa, int beta, int altura);

int maxmin( int** board, int fichasRestantes , vector<int>& primDisp, int& posicionesDisp, int alfa, int beta, int altura){

    if( maxMio >= c ){ // si gano yo
        return 1;
    } 
    
    if( maxCont >= c ){ // si gana el
        return -1;
    }
    
    if( fichasRestantes == 0 || posicionesDisp == 0 ){ // si empatamos
        return 0;
    }
    
    int movimiento = -2;
    int res = -100;
    int i = 0;
    int aux, aux2, aux3, actual;
    while(i < columns){
        aux = primDisp[i]; // si tengo posibilidad de poner la ficha
        if (aux < rows){
            if (!(i > 0 && res >= beta)){ // poda
            board[aux][i] = 1; 
            aux2 = maxMio;
            primDisp[i]++;
            puntosNuevaFicha(aux, i, maxMio, board, 1); // "coloco" la ficha y llamo a la recursion con el nuevo valor de maxMio
            fichasRestantes--;
            posicionesDisp--;
            altura++;
                actual = minmax(board, fichasRestantes, primDisp, posicionesDisp,  alfa,  beta, altura); // recursion con el elemento
                altura--;
                posicionesDisp++;
                board[aux][i] = -1; // deshago el colocar ficha
                maxMio = aux2;
                primDisp[i]--;
                fichasRestantes++;
                if (actual > res){ // calculo el maximo por cada columna
                    res = actual;
                    movimiento = i;
                } 
                if (res > alfa) alfa = res; // actualizo alfa
            }
        }
        i++;
    }
    if(altura == 0){
        return movimiento; // solo retorno el movimiento a hacer si soy uno de los primeros hijos
    }
    return res;
}

int minmax(int** board, int fichasRestantes, vector<int>& primDisp, int& posicionesDisp, int alfa, int beta, int altura){

    if( maxMio >= c ){
        return 1;
    } 
    
    if( maxCont >= c ){
        return -1;
    }
    
    if( fichasRestantes == 0 || posicionesDisp == 0 ){
        return 0;
    }
    
    int res = 100;
    int i = 0;
    int aux, aux2, aux3, actual;
    while(i < columns ){
        aux = primDisp[i];
        if (aux < rows){
            if (!(i > 0 && res <= alfa)){
            board[aux][i] = 0;
            aux2 = maxCont;
            primDisp[i]++;
            puntosNuevaFicha(aux, i, maxCont, board, 0);
            fichasRestantes--;
            posicionesDisp--;
            altura++;
                actual = maxmin( board, fichasRestantes, primDisp, posicionesDisp, alfa, beta, altura); // recursion con el elemento
                altura--;
                posicionesDisp++;
                fichasRestantes++;
                primDisp[i]--;
                board[aux][i] = -1;
                maxCont = aux2;
                if (actual < res){
                   res = actual;
                }
                if (res < beta) beta = res;
            }
        }
        i++;
    }
    return res; 
}





int main() {

    ofstream outputime;
    outputime.open("tiempoback.txt");

    int **board;
    while (true) {
        color = read_str();
        oponent_color = read_str();
        columns = read_int();
        rows = read_int();
        c = read_int();
        p = read_int();

        int posicionesDisp = columns*rows; // va de n*m a 0
        maxCont = 0; // maximo valor del contratio
        maxMio = 0; // maximo valor del backtraking

        vector<int> primDisp; // es el vector de posiciones disponibles de cada columna
        int z = 0;
        while(z < columns){
            primDisp.push_back(0);
            z++;
        }
       
        board = new int*[columns]; // matriz donde en cada casilla va 1 si la ficha es del algoritmo, 0 si es del contrario, y -1 si no hay ficha

        for(int x = 0; x < rows; x++){
            board[x] = new int[columns];
        }
        int i = 0;
        while(i < rows){
            int j = 0;
            while(j < columns){
                board[i][j] = -1;
                j++;
            }
        i++;
        }
        int fichasRestantes = p;

        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        go_first = read_str();
        if (go_first == "vos") {
                int res;
                res = maxmin(board,fichasRestantes, primDisp, posicionesDisp, -100, 100, 0); //alfa, beta, altura
                board[primDisp[res] ][res] = 1; //actualizo mi movimiento
                primDisp[res]++; 
                posicionesDisp--;
                send(res);
        }

        while (true) {

            maxCont = 0;
            maxMio = 0;

            msg = read_str();
            if (msg == "ganaste" || msg == "perdiste" || msg == "empataron") {
                high_resolution_clock::time_point t2 = high_resolution_clock::now();
                duration<double> time_span1 = duration_cast<duration<double>>(t2 - t1);
                outputime << time_span1.count() << endl;
                break;
            }
            posicionesDisp--;
            col = stoi(msg);
            int fila = primDisp[col];
            board[fila][col] = 0; // actualizo el mov del contrario
            fichasRestantes--;
            primDisp[col]++;
            puntosNuevaFicha(fila, col, maxCont, board, 0); // actualizo el maximo valor asta ahora del contrario
            int res;
            res = maxmin(board,fichasRestantes, primDisp, posicionesDisp, -100, 100, 0); //alfa, beta, altura
            board[primDisp[res] ][res] = 1; //actualizo mi movimiento
            primDisp[res]++;
            posicionesDisp--;
            send(res);
        }
    }

outputime.close();
    int x = 0;
    while(x <= columns){
        delete[] board[x];
        x++;
    }

    delete[]board;

    return 0;
}
