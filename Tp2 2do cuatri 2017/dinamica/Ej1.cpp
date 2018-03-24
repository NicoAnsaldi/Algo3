#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <tuple>
#include <time.h> 
#include <stdio.h> 
#include <ctime>
#include <ratio>
using namespace std;

#include <chrono>
using namespace std::chrono;

#define INFINITO 273890

int maquinolas(int cantTrabajos, int** Costo, int** MatrizResultado, vector<int>& m1){
	
	vector<int> Indices;
	for(int i = 2; i <= cantTrabajos; i++){
		int indice;
		int minimo = INFINITO;
		for(int j = 0; j < i; j++){

			MatrizResultado[i][j] = MatrizResultado[i-1][j] + Costo[i][i-1];
			
			
			if(minimo > MatrizResultado[i-1][j] + Costo[i][j]){
				minimo = MatrizResultado[i-1][j] + Costo[i][j];
				indice = j;
			}
		}
		Indices.push_back(indice);
		MatrizResultado[i][i-1] = minimo; // con esto voy colocando el minimo en la matriz
		
	}

	vector< tuple<int, int> > Camino;
	int res = INFINITO;
	int indice = INFINITO;
	for(int i = 0; i < cantTrabajos; i++){
		if(res > MatrizResultado[cantTrabajos][i]){ //este for devuelve el resultado final
			res = MatrizResultado[cantTrabajos][i];
			indice = i;
		}
	}

	for(int i = cantTrabajos; i > 1; i --){ // este for genera tuplas con los trabajos
		Camino.push_back(make_tuple(i, indice));	
		if(MatrizResultado[i-1][indice] == INFINITO){
			indice = Indices[i-2];
		}
	}

	m1.push_back(1);
	for(int i = cantTrabajos-2; i >= 0; i--){ // este for toma los trabajos que corresponden al resultado
		if(m1.back() != get<1>(Camino[i])){
			m1.push_back((int)get<0>(Camino[i])); 
		}
	}

	return res;
}


int main (){
	int cantTrabajos;
	cin >> cantTrabajos;// levanto la cantidad de trabajos
	
	while(cantTrabajos != 0){ // para levantar varias instancias
	
	int i = 0;
	int** Costos = new int*[(cantTrabajos+1)]; // costos es un doble puntero a un arreglo de punteros
	int** MatrizResultado = new int*[(cantTrabajos+1)]; // matriz tmb
	while(i <= cantTrabajos){
		MatrizResultado[i] = new int[(cantTrabajos)]; // Le asigno a cada puntero un arreglo // este while toma n
		i++;
	}
	i= 0;
	while(i <= cantTrabajos){
		int j = 0;
		while(j < cantTrabajos){
			MatrizResultado[i][j] = INFINITO; // se inicializa la matriz en "infinito" // este while toma n*n
			j++;
		}
		i++;
	}

	i = 0;
	while(i <= cantTrabajos){
		int j = 0;
		Costos[i] = new int[(i+1)]; // aca se levantan la matriz de costos que es solo la mitad con la diagonal incluida, lo demas no se toca.
		while(j < i){
			int aux;
			cin >> aux;
			Costos[i][j] = aux; // este while toma n*n
			j++;
		}
		i++;
	}

	MatrizResultado[1][0] = Costos[1][0];

	vector<int> m1;
	int res = 0; 
	//high_resolution_clock::time_point t1 = high_resolution_clock::now();
	
	res = maquinolas(cantTrabajos, Costos, MatrizResultado, m1);
	
	//high_resolution_clock::time_point t2 = high_resolution_clock::now();
	//duration<double> time_span1 = duration_cast<duration<double>>(t2 - t1);
	//cout << time_span1.count() << endl; 
	
	cout << res << " ";
	
	for(int i = 0; i < m1.size(); i++){
		cout << m1[i] << " ";
	}
	cout << endl;

	i = 0;
	while(i <= cantTrabajos){
		delete[] Costos[i];
		delete[] MatrizResultado[i] ; // dado que pedimos con new, para no perder memoria, liberamos lo pedido
		i++;
	}

	delete[]Costos;
	delete[]MatrizResultado;

	cin >> cantTrabajos; // el cin para levantar varias instancias
	}
	return 0;
}



