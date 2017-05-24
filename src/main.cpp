// Erstmal keine GUI in main.cpp
#include <iostream>
#include "rohr.h"
#include "fluid.h"
#include "stroemung.h"

#define TEST
#include "tests/testDefinitionen.h"

using namespace std;

int main(){
    RUNTEST

    double l_in = 0;
    double r_in = 0;
    
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
    double massenstrom_in = 10;
    double dichte_in = 1000;
    double nue_in = 5e-6;

    // Verschiedene Standardfluide definieren (bei 20°C)
    Fluid fluid(dichte_in, nue_in);
    fluid.set_massenstrom(massenstrom_in);

    // Rohrströmung zusammenbauen
    Rohrstroemung rohrstroemung(rohr, fluid);
    cout << "Rohrreibungsbeiwert: " << rohrstroemung.get_lambda() << endl;
    cout << "Strömungsgeschwindigkeit: " << rohrstroemung.get_speed() << endl;
    cout << "Reynoldszahl: " << rohrstroemung.get_Re() << endl;

    return 0;
}
