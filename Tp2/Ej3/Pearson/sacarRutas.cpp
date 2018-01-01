#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <time.h> 
#include <stdio.h> 
using namespace std;

int main (){
    int rutas;
    int fabricas;
    int clientes;
    int prim;
    int sec;
    int peso;
    int n;
    int m = 0;

    cin >> fabricas;
    cin >> clientes;
    cin >> rutas;

    n = rutas;
    while (true){

        while (n > 0){
            cin >> prim;
            cin >> sec;
            cin >> peso;
            n--;
        }
        if (m % 100 == 0) cout << fabricas << ' ' << clientes << ' ' << rutas << endl;
        //cout << fabricas << ' ' << clientes << ' ' << rutas << endl;

        cin >> fabricas;
        if (fabricas == 0) break;
        cin >> clientes;
        cin >> rutas;
        n = rutas;
        m++;
    }
    return 0;
}
