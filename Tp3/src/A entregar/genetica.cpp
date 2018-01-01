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
#include <tuple>
#include <time.h>
#include <iomanip>

using namespace std;
int cantidadDePesos = 8+7;
int jugadores = 10;
string msg;
float elMejor = 1000;
vector<int> elMejorv;
ofstream plotter;

int in(vector<int> vector, int elem){
	int n = 0;
	while (n < vector.size()){
		if (elem == vector[n]) return 1;
		n++;
	}
	return 0;
}

float promedio(vector<float> vector){
	int n = 0;
	float res = 0;
	while (n < vector.size()){
		res = res + vector[n];
		n++;
	}
	return res/vector.size();
}



int maxVector(vector<float> pesos){
	int n = 0;
	float max = pesos[0];
	int res = 0;
	while (n < pesos.size()){
		if (max > pesos[n]){
			max = pesos[n];
			res = n;
		} 
		n++;
	}
	return res;
}


vector<vector<int>> soyAdoptado(vector<vector<int>> poblacion){

	ofstream output;
	ifstream input;
	vector< float > rank;
	vector<vector<int>> poblacionaux = poblacion;

	for(int i = 0; i < jugadores; i++){ 
		vector<int> pesos = poblacion[i];

		output.open("input.txt");
		for(int i = 0; i < cantidadDePesos; i++){
			output << pesos[i]; // leo la poblacion que me pasan y dejo jugador por jugador en el input asi lo toma el ej3.cpp y juega.
			output << " ";
		}
		output.close();

		int ganadas = 0;
		int perdidas = 0;
		int empatadas = 0;

		system("python c_linea.py --blue_player ./ej3 --red_player ./champ --first rojo --columns 7 --rows 6 --p 500 --c 4 --iterations 100");

		input.open("output.txt");
		for(int i = 0; i < 100; i++){
			input >> msg;
			if (msg == "ganaste") ganadas++;
	    	if (msg == "perdiste") perdidas++;
	    	if (msg == "empataron") empatadas++;
		}
	    input.close();
		cout << "Gano " << ganadas << " Empato " << empatadas << " Perdio " << perdidas << endl;
		float aux = (float) perdidas/ (float) 100; // fitness de porcentaje de ganado o empatado
		rank.push_back(aux);

		 // fitnes con puntaje
		//int aux = 100 + 15*ganadas + 10*empatadas - perdidas;
		//rank.push_back(aux);
		// para tomar esta fitness se debe modificar la funcion maxVector para que tome el maximo efectivamente, 
		// y al buscar elMejor, se debe poner su incializacion en un numero bajo, y modificar mas adelante, cuando lo tomamos en cada iteracion.
		
	}

	// metodo de seleccion random
	
	//int padre1 = rand()%10; // indice

	// metodo de seleccion ponderado.

	int padre1 = maxVector(rank); // indice

	plotter << fixed << setprecision(2) << rank[padre1] << endl;
	cout << " MAX  ES "   << fixed << setprecision(2) << rank[padre1] << endl;
	cout << " Promedio es " << fixed << setprecision(2) << promedio(rank) << endl;

	if (rank[padre1] <= elMejor){
		elMejor = rank[padre1];
		elMejorv = poblacion[padre1];
	}
	vector<int> padre1v = poblacion[padre1];

	for(int i = 0; i < jugadores; i ++){  
		vector<int> hijo = poblacionaux[i];

		for(int i = 0; i < cantidadDePesos; i+=2){
			if((rand()%10) > 4){
				hijo[i] = padre1v[i];
				hijo[i+1] = padre1v[i+1];
			}
		}
		poblacion[i] = hijo;
	}

	for(int i = 0; i < jugadores; i++){
		vector<int> pesos = poblacion[i];

		for(int i = 0; i < cantidadDePesos; i++){ // mutacion
			if((rand()%10) > 9){ // 0.1
				if((rand()%10) > 4){
					pesos[i] = rand() % 100 ; // muta en positivos
				}else{
					pesos[i] = (rand()%100)*(-1);// muta en negativos
				}
			}
		}
	}


	return poblacion;
}

int main(){

	system("g++ -std=c++11 -g ej3.cpp -o ej3");
	system("g++ -std=c++11 -g champ.cpp -o champ");
	plotter.open("genneticsselecrandom.txt");

	vector<vector<int>> poblacion;
	srand(time(NULL));
	for(int i = 0; i < jugadores; i++){ // mi poblacion es de 10, genero los 10 jugadores de 18 pesos randoms para la primera generacion
		vector<int> pesos;
		for(int i = 0; i < cantidadDePesos; i++){
			if((rand()%10) > 5){
				pesos.push_back(rand() % 100);
			}else{
				pesos.push_back((rand()%100)*(-1));
			}
		}
		poblacion.push_back(pesos);
	}

	vector<vector<int>> res = poblacion;

	for(int i = 0; i < jugadores; i++){
			cout << "Jugador " << i << endl;
			vector<int> pesos = res[i];
				cout << " { ";
			for(int j = 0; j < cantidadDePesos; j++){
				cout << pesos[j] << " ";
			}
			cout << " } " << endl;
		}


	for(int i = 0; i < 50; i++){
		res = soyAdoptado(res);
	
		cout << " Generacion "   << i+1 << endl;
		
		cout << "El mejor hasta ahora fue " << fixed << setprecision(2) << elMejor << endl;
		cout << " { ";
		for(int j = 0; j < cantidadDePesos; j++){
			cout << elMejorv[j] << " ";
		}
		cout << " } " << endl;
		cout << " ------------------------------------------------- " << endl;
		
		for(int i = 0; i < jugadores; i++){
			cout << "Jugador " << i << endl;
			vector<int> pesos = res[i];
				cout << " { ";
			for(int j = 0; j < cantidadDePesos; j++){
				cout << pesos[j] << " ";
			}
			cout << " } " << endl;
		}
	}
	
	cout << "El mejor historico fue " << fixed << setprecision(2) << elMejor << endl;
	cout << " { ";
	for(int j = 0; j < cantidadDePesos; j++){
		cout << elMejorv[j] << " ";
	}
	cout << " } " << endl;

	plotter.close();
	system("python plot.py");
	return 0;
}

