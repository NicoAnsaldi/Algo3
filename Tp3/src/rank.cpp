#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <sys/stat.h>
using namespace std;

string msg;

void send(const string& msg) {
    cout << msg << endl;
}

void send(int msg) {
    cout << msg << endl;
}

int read_int() {
    string msg;
    cin >> msg;
    if (msg == "salir") {
        send("listo");
        exit(0);
    }
    return stoi(msg);
}

string read_str() {
    string msg;
    cin >> msg;
    if (msg == "salir") {
        send("listo");
        exit(0);
    }
    return msg;
}

int main() {

    ifstream input;
    input.open ("output.txt");
    int ganadas = 0;
    int perdidas = 0;
    int empatadas = 0;
    int n = 100;

    while (n > 0) {
        input >> msg;
        if (msg == "ganaste") ganadas++;
        if (msg == "perdiste") perdidas++;
        if (msg == "empataron") empatadas++;
        n--;
    }
    cout << "Gano " << ganadas << " Empato " << empatadas << " Perdio " << perdidas << endl;

    input.close();
    return 0;

}

