#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int bactracking(vector <pair <int, int> >*, int, int*, vector<int>*);
void Confiable(int*,vector<int>*,vector <pair <int, int> >*, int);
void NoConfiable(int*,vector<int>*,vector <pair <int, int> >*, int);
bool VerConfiabilidad(vector <pair <int, int> >*, int, vector<int>*);

int main(){
	while(true){
		int res = 0;
		int agentes;
		int cantEncuestas;
		cin >> agentes;
		cin >> cantEncuestas;

		vector<pair <int, int> > Encuestas;
		vector<int> res;

		if(agentes > 0 && cantEncuestas >= 0){
			while(cantEncuestas >= 0){
				int a;
				int b;
				cin >> a;
				cin >> b;
				Encuestas.push_back(pair <int,int>(a,b));
				cantEncuestas--;
			}
				int a = 1;
				cout << bactracking(&Encuestas, agentes,&a, &res);
		}
		if(agentes == 0 and cantEncuestas ==0){
			break;
		}
	}
	return 0;
}

int bactracking(vector <pair <int, int> >* encuestas, int agentes, int* i, vector<int>* res){
	if(*i > agentes){
		return *res.size();
	}
	Confiable(i, res, encuestas, agentes);
	NoConfiable(i, res, encuestas, agentes);


	return 0;
}

void Confiable(int* i,vector<int>*res,vector <pair <int, int> >* Encuestas, int agentes){
	if(*i<=agentes){
		if((VerConfiabilidad(Encuestas, *i, res))){
			*res++;
		}
			*i++;
			bactracking(Encuestas, agentes, i, 	res);
	}
	return;
}

void NoConfiable(int* i,vector<int>* res,vector <pair <int, int> >* Encuestas, int agentes){
	if(*i<=agentes){
		*i++;
		bactracking(Encuestas, agentes, i, res);
	}
	return;
}


bool VerConfiabilidad(vector <pair <int, int> >* Encuestas, int a, vector <int>* res){
	int n = 0;
	while(n < *Encuestas.size()){

	}
}