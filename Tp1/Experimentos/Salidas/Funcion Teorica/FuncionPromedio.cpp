#include <iostream>
#include <vector>

using namespace std;

int main(){
	int agentes;
	int cantEncuestas;
	while(true){
		int res = 0;
		int i = 0;
		while(i < 100){
			cin >> agentes;
			cin >> cantEncuestas;
			if(agentes == 0 && cantEncuestas == 0){
				return 0;
			}
			res += cantEncuestas;
			i++; 
		}
		cout << agentes << " " << (res/100) << endl;	
	}
	return 0;
}