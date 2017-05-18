// Erstmal keine GUI in main.cpp
#include <iostream>
#include "rohr.h"
#include "fluid.h"
#include "stroemung.h"

using namespace std;

int main(){
    double l_in = 0;
    double r_in = 0;
    double massenstrom_in = 0;
    double dichte_in = 0;
    double nue_in = 0;
    
    // Rohrparameter abfragen
    cout << "Rohrparameter eingeben\n" << "##########" << endl;
    cout << "Länge: ";
    cin >> l_in;
    cout << "Radius: ";
    cin >> r_in;

    // Rohrobjekt mit übergebenen Parametern initalisieren
    Rohr rohr(l_in, r_in);
    cout << "Rohrquerschnitt: " << rohr.get_querschnitt() << endl;

    // Fluid initialisieren
    Fluid fluid(dichte_in, massenstrom_in, nue_in);

    // Rohrströmung zusammenbauen
    Rohrstroemung rohrstroemung(rohr, fluid);
    cout << "Rohrreibungsbeiwert: " << rohrstroemung.get_lambda() << endl;

    return 0;
}
