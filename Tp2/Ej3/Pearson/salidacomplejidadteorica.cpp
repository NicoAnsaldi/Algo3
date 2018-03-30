#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <time.h> 
#include <stdio.h> 
using namespace std;

int main(){
    int fabricas;
    int clientes;
    int rutas;
    while(true){
        cin >> fabricas;
        cin >> clientes;
        cin >> rutas;

        if(fabricas == 0) break;
        cout << pow( clientes, 2)<<endl;
    }
    return 0;
}