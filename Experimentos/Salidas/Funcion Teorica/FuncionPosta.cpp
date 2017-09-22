#include <iostream>
#include <math.h>

using namespace std;

int main(){
	double agentes;
	double cantEncuestas;
	while(true){
		cin >> agentes;
		cin >> cantEncuestas;
		if(agentes == 0 && cantEncuestas == 0){
			return 0;
		}
		cout << (pow(2, agentes) * (agentes * (pow(cantEncuestas, 2))) + (pow(agentes, 2) * cantEncuestas))<<endl;
		//cout << (pow(2, agentes) * (agentes * (pow(cantEncuestas, 2))))<<endl;
	}
	return 0;
}