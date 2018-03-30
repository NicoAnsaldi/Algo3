#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <sys/stat.h>


using namespace std;

ofstream output;
ifstream input;
string msg;


void mostrarVector(vector<int> v);
void copiarVector(vector<int>& v1, vector<int> v2);
void inicializarVector(vector<int>& v1, int parametros, int valor);
void cargarOutput(vector<int> pesos, vector<int>& resultado, int indice1, int indice2, int inc1, int inc2);
int cantPartidasG(int cantidadPartidas);
void cargarPesos(vector<int>&, int);
void vaciarVector(vector<int>&);

void gridRecorro(int cantColumnas, int cantFilas, int C, int cantFichas, int cantPartidas, string nombre);

int main(){
	gridRecorro(7, 6, 4, 21, 20, "ID");
	return 0;
}




void gridRecorro(int cantColumnas, int cantFilas, int C, int cantFichas, int cantPartidas, string nombre){
	
	int parametros = 8+cantColumnas;

	system("g++ -g -std=c++11 -o ej3Grid ej3Grid.cpp");
	system("g++ -g -std=c++11 -o champ champ.cpp");
	string b = "python2 c_linea.py --blue_player ./ej3Grid --red_player ./champ --columns " + to_string(cantColumnas) + " --rows " + to_string(cantFilas);
	b = b + " --p " + to_string(cantFichas) + " --c " + to_string(C) + " --iterations " + to_string(cantPartidas) + " --first rojo";
	const char* comando = b.c_str();


	output.open("inputGrid.txt");
	for(int j = 0; j< parametros;j++){
		int aux2 = rand() %100;
		if(rand() % 10 > 5){
			output << aux2 << " ";
		}else{
			output << (aux2*-1) << " ";
		}
	}
	output.close();

	int r = 0;
	if(cantColumnas % 2 == 1){
		r = 8+cantColumnas-1;
	}else{
		r = 8+cantColumnas;
	}
	
	vector<int> resultado;
	
	vector<int> pesos;
	int porcentaje = 0;
	int repeticiones = 0;

	int k = rand()%10;
	inicializarVector(resultado, parametros, k);

	
	cargarPesos(pesos, parametros);

	for(int z = 0; z < r; z+=2){
		int peso1 = 0;
		int peso2 = 0;
		porcentaje = 0;
			
		for(int i = -15; i < 15; i++){
			for(int j = -15;j< 15; j++){

				cargarOutput(pesos, resultado, z, z+1, i, j);
				system(comando);
					
				int porcentajeAux = cantPartidasG(cantPartidas);
				remove("outputGrid.txt");
					
				if(porcentajeAux > porcentaje){
					peso1 = pesos[z]+i;
					peso2 = pesos[z+1]+j;
					porcentaje = porcentajeAux;
				}
			}
		}
		pesos[z] = peso1;
		pesos[z] = peso2;
	}
		
	if(cantColumnas % 2 == 1){
		int pesoz = 0;
		porcentaje = 0;
		for(int i = -15; i<15; i++){
				
			cargarOutput(pesos, resultado, r, r-1, i, 0);
				
			system(comando);
				
			int porcentajeAux = cantPartidasG(cantPartidas);
				
			remove("outputGrid.txt");
			if(porcentajeAux > porcentaje){
				pesoz = pesos[r] + i;
				porcentaje = porcentajeAux;
			}
				
		}
		pesos[r] = pesoz;
		cargarOutput(pesos, resultado, r, r, 0, 0);
	}

	vaciarVector(pesos);
}

void vaciarVector(vector<int>& v1){
	while(v1.size() > 0){
		v1.pop_back();
	}
}

void mostrarVector(vector<int> v){
	for(int x = 0; x < v.size();x++){
		cout << v[x] << " ";
	}
	cout << endl;
}

void copiarVector(vector<int>& v1, vector<int> v2){
	for(int i = 0; i < v2.size(); i++){
		v1[i] = v2[i];
	}
}

void inicializarVector(vector<int>& v1, int parametros, int valor){
	for(int x = 0; x < parametros; x++){
		if(valor == -1){
			v1.push_back(x);
		}else{
			v1.push_back(valor);
		}
	}
}

void cargarOutput(vector<int> pesos, vector<int>& resultado, int indice1, int indice2, int inc1, int inc2){
	resultado[indice1] = pesos[indice1] + inc1;
	resultado[indice2] = pesos[indice2] + inc2;
	output.open("inputGrid.txt");
	for(int x = 0; x < resultado.size(); x++){
		output << resultado[x] << " ";
	}
	output.close();
}

int cantPartidasG(int cantidadPartidas){
	int ganadas = 0;
	int empatadas = 0;
	int perdidas = 0;
	input.open("outputGrid.txt");
	for(int y = 0; y < cantidadPartidas; y++){
		input >> msg;
		if (msg == "ganaste") ganadas++;
		if (msg == "perdiste") perdidas++;
		if (msg == "empataron") empatadas++;
	}
	input.close();

	return (ganadas*100/cantidadPartidas);
}

void cargarPesos(vector<int>& v1, int parametros){
	input.open("inputGrid.txt");
	for(int i = 0; i< parametros;i++){
		int aux;
		input >> aux;
		v1.push_back(aux);
	}	
	input.close();
}






