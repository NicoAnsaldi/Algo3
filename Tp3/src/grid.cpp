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
void generarRandom(vector<int>&, int);
bool en(int, vector<int>&);
void ordenCapicua(vector<int>&, int);
void vaciarVector(vector<int>&);
void Grasp(vector<int>&, int);

void gridRecorro(int cantColumnas, int cantFilas, int C, int cantFichas, int cantPartidas, vector<int>& orden, string nombre);
void gridGraspRecorro(int cantColumnas, int cantFilas, int C, int cantFichas, int cantPartidas, vector<int>& orden, string nombre);

int main(){
	srand(time(NULL));
	
	vector<int> orden;
	inicializarVector(orden, 15, -1);
	cout << "dale con ID" << endl;
	gridRecorro(7, 6, 4, 21, 20, orden, "ID");

	vaciarVector(orden);
	generarRandom(orden, 15);
	cout << "dale con Random" << endl;
	gridRecorro(7, 6, 4, 21, 20, orden, "Random");

	ordenCapicua(orden, 15);
	cout << "dale con Capicua" << endl;
	gridRecorro(7, 6, 4, 21, 20, orden, "Capicua");

	vaciarVector(orden);
	inicializarVector(orden, 15, -1);
	cout << "dale con Grasp" << endl;
	gridGraspRecorro(7, 6, 4, 21, 20, orden, "Grasp");

	return 0;
}




void gridRecorro(int cantColumnas, int cantFilas, int C, int cantFichas, int cantPartidas, vector<int>& orden, string nombre){
	
	int parametros = 8+cantColumnas;

	string b = "python2 c_linea.py --blue_player ./ej3N --red_player ./champ --columns " + to_string(cantColumnas) + " --rows " + to_string(cantFilas);
	b = b + " --p " + to_string(cantFichas) + " --c " + to_string(C) + " --iterations " + to_string(cantPartidas) + " --first rojo";
	const char* comando = b.c_str();


	output.open("inputNico.txt");
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

	while(repeticiones < 15){
		cout << repeticiones << endl;
		cargarPesos(pesos, parametros);

		int k = rand()%10;
		inicializarVector(resultado, parametros, k);
		
		for(int z = 0; z < r; z+=2){
			int peso1 = 0;
			int peso2 = 0;
			porcentaje = 0;
			

			for(int i = -15; i < 15; i++){
				for(int j = -15;j< 15; j++){

					cargarOutput(pesos, resultado, orden[z], orden[z+1], i, j);

					system(comando);
					
					int porcentajeAux = cantPartidasG(cantPartidas);
					remove("outputNico.txt");
					
					if(porcentajeAux > porcentaje){
						peso1 = pesos[orden[z]]+i;
						peso2 = pesos[orden[z+1]]+j;
						porcentaje = porcentajeAux;
					}
				}
			}
			pesos[orden[z]] = peso1;
			pesos[orden[z+1]] = peso2;
		}
		
		
		if(cantColumnas % 2 == 1){
			int pesoz = 0;
			porcentaje = 0;
			for(int i = -15; i<15; i++){
				
				cargarOutput(pesos, resultado, orden[r], orden[r-1], i, 0);
				
				system(comando);
				
				int porcentajeAux = cantPartidasG(cantPartidas);
				
				remove("outputNico.txt");
				if(porcentajeAux > porcentaje){
					pesoz = pesos[orden[r]] + i;
					porcentaje = porcentajeAux;
				}
				
			}
			pesos[orden[r]] = pesoz;
			cargarOutput(pesos, resultado, orden[r], orden[r], 0, 0);
		}

		string nombreArchivo = "SalidaGridRecorro"+ nombre +".txt";
		const char* archivo = nombreArchivo.c_str();
		
		output.open(archivo, std::ofstream::out | std::ofstream::app);
		output << repeticiones << " " << porcentaje << endl;
		output.close();

		if(nombre == "Random"){
			vaciarVector(orden);
			generarRandom(orden, parametros);
		}
		vaciarVector(resultado);
		vaciarVector(pesos);
		repeticiones++;
	}
	system("reset");
}


void generarRandom(vector<int>& v1, int parametros){

	while(v1.size() != parametros){
		int indiceAAgregar = rand() % parametros;
		while(en(indiceAAgregar, v1)){
			indiceAAgregar = rand() % parametros;
		}
		v1.push_back(indiceAAgregar);
	}

}

bool en(int a, vector<int>& v1){
	for(int i = 0; i < v1.size(); i++){
		if(v1[i] == a){
			return true;
		}
	}
	return false;
}

void ordenCapicua(vector<int>& v1, int parametros){
	int j = 0;
	for(int i = 0; i < (parametros/2); i++){
		v1[j] = i;
		v1[j+1] = (parametros-(i+1));
		j+=2;
	}
	if(parametros%2 == 1){
		v1[(parametros-1)] = (parametros/2);
	}
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
	output.open("inputNico.txt");
	for(int x = 0; x < resultado.size(); x++){
		output << resultado[x] << " ";
	}
	output.close();
}

int cantPartidasG(int cantidadPartidas){
	int ganadas = 0;
	int empatadas = 0;
	int perdidas = 0;
	input.open("outputNico.txt");
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
	input.open("inputNico.txt");
	for(int i = 0; i< parametros;i++){
		int aux;
		input >> aux;
		v1.push_back(aux);
	}	
	input.close();
}

void Grasp(vector<int>& v1, int cantidad){
	for(int i = 0; i < cantidad; i++){
		int aux = rand()%100;
		if(rand() % 10 > 4){
			v1.push_back(aux);
		}else{
			v1.push_back(aux*-1);
		}
	}
}



void gridGraspRecorro(int cantColumnas, int cantFilas, int C, int cantFichas, int cantPartidas,vector<int>& orden, string nombre){
	
	int parametros = 8+cantColumnas;

	string b = "python2 c_linea.py --blue_player ./ej3N --red_player ./champ --columns " + to_string(cantColumnas) + " --rows " + to_string(cantFilas);
	b = b + " --p " + to_string(cantFichas) + " --c " + to_string(C) + " --iterations " + to_string(cantPartidas) + " --first rojo";
	const char* comando = b.c_str();


	output.open("inputNico.txt");
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
	vector<int> grasp1;
	vector<int> grasp2;
			

	while(repeticiones < 15){
		cout << repeticiones << endl;
		cargarPesos(pesos, parametros);

		int k = rand()%10;
		inicializarVector(resultado, parametros, k);
		
		for(int z = 0; z < r; z+=2){
			int peso1 = 0;
			int peso2 = 0;
			porcentaje = 0;
			
			Grasp(grasp1, 5);
			Grasp(grasp2, 5);
			
			for(int indice = 0; indice < grasp1.size(); indice++){
				for(int i = -15; i < 15; i++){
					for(int j = -15;j< 15; j++){

						cargarOutput(pesos, resultado, orden[z], orden[z+1], (grasp1[indice]+i), (grasp2[indice]+j));

						system(comando);
					
						int porcentajeAux = cantPartidasG(cantPartidas);
						remove("outputNico.txt");
					
						if(porcentajeAux > porcentaje){
							peso1 = pesos[orden[z]]+grasp1[indice]+i;
							peso2 = pesos[orden[z+1]]+grasp2[indice]+j;
							porcentaje = porcentajeAux;
						}
					}
				}
			}

			vaciarVector(grasp1);
			vaciarVector(grasp2);
			pesos[orden[z]] = peso1;
			pesos[orden[z+1]] = peso2;
		}
		
		
		if(cantColumnas % 2 == 1){
			int pesoz = 0;
			porcentaje = 0;
			vector<int> grasp3;
			Grasp(grasp3, 5);
			for(int j = 0; j < grasp3.size(); j++){
				for(int i = -15; i<15; i++){
				
					cargarOutput(pesos, resultado, orden[r], orden[r-1], (grasp3[j]+i), 0);
				
					system(comando);
				
					int porcentajeAux = cantPartidasG(cantPartidas);
				
					remove("outputNico.txt");
					if(porcentajeAux > porcentaje){
						pesoz = pesos[orden[r]]+grasp3[j] + i;
						porcentaje = porcentajeAux;
					}
				
				}
				pesos[orden[r]] = pesoz;
				cargarOutput(pesos, resultado, orden[r], orden[r], 0, 0);
			}
		}

		string nombreArchivo = "SalidaGridRecorro"+ nombre +".txt";
		const char* archivo = nombreArchivo.c_str();
		
		output.open(archivo, std::ofstream::out | std::ofstream::app);
		output << repeticiones << " " << porcentaje << endl;
		output.close();

		if(nombre == "Random"){
			vaciarVector(orden);
			generarRandom(orden, parametros);
		}
		vaciarVector(resultado);
		vaciarVector(pesos);
		repeticiones++;
	}
	system("reset");
}

