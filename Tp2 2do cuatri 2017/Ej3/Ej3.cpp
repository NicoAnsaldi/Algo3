#include <iostream>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define INFINITO 21474836

void Prim(int** ,int, int, int*);
void PintandoRutas(int,int*, int**);


int main(){
int aux ;
cin >> aux;
    while( aux != 0){
    //clock_t start, end;
    int cantFabricas;
    int cantClientes;
    int cantRutas;
    cantFabricas = aux;
    cin >> cantClientes;
    cin >> cantRutas;

    int cantNodos = cantFabricas + cantClientes;

    int **Aristas;
    Aristas = new int*[cantNodos];

    for(int x = 0; x < cantNodos; x++){
        Aristas[x] = new int[cantNodos];
    }

    int j = 0;
    int i = 0;
    while(i < cantNodos){
        j = 0;
        while(j < cantNodos){
            Aristas[i][j] = INFINITO;
            j++;
        }
        i++;
    }

    i = 0;
    int NodoI;
    int NodoJ;
    int peso;
    //Asumo grafo no orientado
    while(i < cantRutas){
        cin >> NodoI;
        cin >> NodoJ;
        cin >> peso;
        Aristas[NodoI][NodoJ] = peso;
        Aristas[NodoJ][NodoI] = peso;
        i++;
    }
    int* Padres = new int[cantNodos];


    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    Prim(Aristas, 0, cantNodos, Padres);
    
    PintandoRutas(cantFabricas, Padres, Aristas);
    high_resolution_clock::time_point t4 = high_resolution_clock::now();

    duration<double> time_span1 = duration_cast<duration<double>>(t4 - t1);
    //cout << time_span1.count() << endl; 


    int res = 0;
    int contador = 0;
    i = 0;
    while(i < cantNodos){
        if(Padres[i] != -1){
            res += Aristas[i][Padres[i]];
            contador++;
        }
        i++;
    }

    cout << res << " " << contador << " ";
    i = 0;
    while(i < cantNodos){
        if(Padres[i] != -1){
            cout << Padres[i] << " " << i << " ";
        }
        i++;
    }
    cout << endl;
    i = 0;
    while(i < cantNodos){
        delete[] Aristas[i];
        i++;
    }

    delete[] Aristas;
    delete[] Padres;

cin >> aux;
}
    return 0;
}




void Prim (int** matriz, int nodo, int cantNodos, int *Padres){
    int nodosVisitados = 0;
    bool visitados[cantNodos]; 
    int i = 0;
    int pesos[cantNodos];
    int padres[cantNodos];

    while(i < cantNodos){
        pesos[i] = INFINITO;
        visitados[i] = false;
        padres[i] = -1;
        i++;
    }

    i = 0;
    while(i< cantNodos){
        if(matriz[nodo][i] != INFINITO){
            pesos[i] = matriz[nodo][i];
            padres[i] = nodo;
        }
        i++;
    }

    pesos[nodo] = 0;
    visitados[nodo] = true;
    nodosVisitados++;

    while(nodosVisitados < cantNodos){
        int nodoAAgregar = 0;
        int peso = INFINITO+1;
        int j = 0;
        while(j < cantNodos){
            if((peso > pesos[j]) && (visitados[j] == false)){
                peso = pesos[j];
                nodoAAgregar = j;
            }
            j++;
        }
        visitados[nodoAAgregar] = true;
        nodosVisitados++;
        int k = 0;
        while(k < cantNodos){
            if((pesos[k] > matriz[nodoAAgregar][k]) && (visitados[k] == false)){
                pesos[k] = matriz[nodoAAgregar][k];
                padres[k] = nodoAAgregar;
            }
            k++;
        }       
    }

    i = 0;
    while(i < cantNodos){
        Padres[i] = padres[i];
        i++;
    }
}

void PintandoRutas(int cantFabricas, int* Padres, int** Aristas){
    int i = 0;
    int Iterador;
    int RutaMaxima;
    int AristaABorrar;
    int inicio;

    while(i < cantFabricas){
        if(Padres[i] != -1){
            RutaMaxima= -1;
            AristaABorrar = -1;
            inicio = i;
            Iterador = Padres[i];
            while(Iterador >= cantFabricas && Padres[Iterador] != -1){
                if(Aristas[Iterador][Padres[Iterador]] > RutaMaxima){
                    RutaMaxima = Aristas[Iterador][Padres[Iterador]];
                    AristaABorrar = Iterador;
                }   
                Iterador = Padres[Iterador];
            }
            if(Aristas[inicio][Padres[inicio]] > RutaMaxima){
                RutaMaxima = Aristas[inicio][Padres[inicio]];
                AristaABorrar = inicio;
            }
            if(Iterador < cantFabricas){
                    Padres[AristaABorrar] = -1;
            }
        }
        i++;
    }
}