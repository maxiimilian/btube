// Erstmal keine GUI in main.cpp
#include <iostream>
#include "rohr.h"
#include "fluid.h"

using namespace std;

int main(){
    double r_in = 0;
    double l_in = 0;
    
    cout << "Rohrparameter eingeben\n" << "##########" << endl;
    cout << "Radius: ";
    cin >> r_in;
    cout << "Länge: ";
    cin >> l_in;

    // Rohrobjekt mit übergebenen parametern initalisieren
    Rohr rohr(r_in, l_in);
    cout << "Rohrquerschnitt: " << rohr.get_querschnitt() << endl;

    return 0;
}
