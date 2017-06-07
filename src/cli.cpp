#include <iostream>
#include "rohr.h"
#include "fluid.h"
#include "stroemung.h"

#define TEST
#include "tests/testDefinitionen.h"

using namespace std;

void start_cli(){
    // Willkommensnachricht ausgeben
    cout << "**********************************" << endl
         << "* Willkommen bei BTube! (c) 1987 *" << endl
         << "**********************************" << endl << endl; 

    // Rohrparameter abfragen
    double laenge_in = 0;
    double radius_in = 0;
    double alpha_innen = 0;
    double alpha_aussen = 0;
    
    cout << "Rohrparameter eingeben:" << endl
         << "-----------------------" << endl;
    cout << "Länge: ";
    cin >> laenge_in;
    cout << "Radius: ";
    cin >> radius_in;
    cout << "Wärmeübergangsk. Fluid->Rohr [W/(m^2*K)]: "; 
    cin >> alpha_innen;
    cout << "!!! Zur Vereinfachung wird angenommen, dass das Rohr infinitesimal dünn ist !!!" << endl;
    cout << "Wärmeübergangsk. Rohr->Umgebung [W/(m^2*K)]: "; 
    cin >> alpha_aussen;

    // Rohrobjekt mit übergebenen Parametern initalisieren
    Rohr rohr(laenge_in, radius_in);
    rohr.set_alpha_innen(alpha_innen);
    rohr.set_alpha_aussen(alpha_aussen);
    cout << "Rohrquerschnitt: " << rohr.get_querschnitt() << " m^2" << endl << endl;

    // Fluid initialisieren
    double massenstrom_in = 10;
    double dichte_in = 1000;
    double nue_in = 5e-6;
    double cp_in = 4182;
    double t_ein = 180;

    cout << "Fluidparameter eingeben:" << endl
         << "------------------------" << endl;
    cout << "Massenstrom [kg/s]: ";
    cin >> massenstrom_in;
    cout << "Dichte [kg/m^3]: ";
    cin >> dichte_in;
    cout << "kin. Viskosität [m^2/s]: ";
    cin >> nue_in;
    cout << "spez. isobare Wärmekapazität [J/(kg*K)]: ";
    cin >> cp_in;
    cout << "Eintrittstemperatur [K]: ";
    cin >> t_ein;
    cout << endl;

    // Fluidobjekt erstellen
    Fluid fluid(dichte_in, nue_in, cp_in);
    fluid.set_massenstrom(massenstrom_in);
    fluid.set_t_ein(t_ein);


    // Umgebungsparameter eingeben
    double t_aussen = 273; 

    cout << "Umgebungsparameter eingeben:" << endl
         << "----------------------------" << endl;
    cout << "Umgebungstemperatur [K]: "; 
    cin >> t_aussen;
    rohr.set_t_aussen(t_aussen);
    cout << endl;

    // Rohrströmung zusammenbauen
    Rohrstroemung rohrstroemung(rohr, fluid);

    cout << "***************************" << endl
         << "* Berechnete Rohrströmung *" << endl
         << "***************************" << endl; 

    cout << "Rohrreibungsbeiwert [1]: " << rohrstroemung.get_lambda() << endl;
    cout << "Strömungsgeschwindigkeit [m/s]: " << rohrstroemung.get_speed() << endl;
    cout << "Reynoldszahl [1]: " << rohrstroemung.get_Re() << endl;
    cout << "kA [?]: " << rohr.get_kA() << endl;
    cout << "Bauart [?]: " << rohrstroemung.get_bauart() << endl;
    cout << "Epsilon [?]: " <<rohrstroemung.get_epsilon() << endl;
    cout << "Austrittstemperatur [K]: " << rohrstroemung.get_temp() <<endl;

}

void run_tests(){
    RUNTEST
}
