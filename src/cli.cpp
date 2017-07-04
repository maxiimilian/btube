#include <iostream>
#include "rohr.h"
#include "fluid.h"
#include "stroemung.h"
#include "math.h"

#define TEST
#include "tests/testDefinitionen.h"

using namespace std;

void start_cli(){
    // Willkommensnachricht ausgeben
    cout << "**********************************" << endl
         << "* Willkommen bei BTube! (c) 1987 *" << endl
         << "**********************************" << endl << endl; 

    // Rohrparameter abfragen
    double laenge_in;
    double radius_in;
    double k_s_in;
    double alpha_innen;
    double alpha_aussen;
    
    cout << "Rohrparameter eingeben:" << endl
         << "-----------------------" << endl;
    cout << "Länge [m]: ";
    cin >> laenge_in;
    cout << "Radius [m]: ";
    cin >> radius_in;
    cout << "Rohrrauheit [m]: ";
    cin >> k_s_in;
    cout << "Hinweis: Zur Vereinfachung wird angenommen, dass das Rohr infinitesimal dünn ist." << endl;
    cout << "Wärmeübergangsk. Fluid->Rohr [W/(m^2*K)]: ";
    cin >> alpha_innen;
    cout << "Wärmeübergangsk. Rohr->Umgebung [W/(m^2*K)]: "; 
    cin >> alpha_aussen;

    // Rohrobjekt mit übergebenen Parametern initalisieren
    Rohr rohr(laenge_in, radius_in, k_s_in);
    rohr.set_alpha_innen(alpha_innen);
    rohr.set_alpha_aussen(alpha_aussen);
    cout << "Rohrquerschnitt: " << rohr.get_querschnitt() << " m^2" << endl << endl;

    // Fluid initialisieren
    double massenstrom_in;
    double dichte_in;
    double nue_in;
    double cp_in;
    double t_ein;
    double p_in;

    cout << "Fluidparameter eingeben:" << endl
         << "------------------------" << endl;
    cout << "Massenstrom [kg/s]: ";
    cin >> massenstrom_in;
    cout << "Dichte [kg/m^3]: ";
    cin >> dichte_in;
    cout << "Eintrittsdruck [bar]: ";
    cin >> p_in;
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
    rohr.set_startpressure(p_in);

    // Umgebungsparameter eingeben
    double t_aussen = 273; 

    cout << "Umgebungsparameter eingeben:" << endl
         << "----------------------------" << endl;
    cout << "Umgebungstemperatur [K]: "; 
    cin >> t_aussen;
    rohr.set_t_aussen(t_aussen);
    cout << endl;

    // Rohrströmung zusammenbauen
    Rohrstroemung rohrstroemung(&rohr, &fluid);

   // Ergebnisse ausgeben
    cout << "***************************" << endl
         << "* Berechnete Rohrströmung *" << endl
         << "***************************" << endl; 

    // Strömungsmechanische Ausgaben
    cout << "Strömungsgeschwindigkeit [m/s]: " << rohrstroemung.get_speed() << endl;
    cout << "Reynoldszahl [1]: " << rohrstroemung.get_Re() << endl;
    cout << "Rohrreibungsbeiwert [1]: " << rohrstroemung.get_lambda() << endl;
    cout << "Austrittsdruck [bar]: " << rohrstroemung.get_pressure(rohr.get_laenge()) << endl;
    cout << "Druckverlust [bar]: " << fabs(p_in - rohrstroemung.get_pressure(rohr.get_laenge())) << endl;

    // Thermodynamische Ausgaben
    cout << "Wärmeübertragungsfähigkeit kA [W/K]: " << rohr.get_kA() << endl;
    cout << "Austrittstemperatur [K]: " << rohrstroemung.get_temp() << endl;
    cout << "Temperaturdifferenz [K]: " << fabs(t_ein - rohrstroemung.get_temp(rohr.get_laenge())) << endl << endl;

    // Abfrage, ob Strömungsprofil berechnet werden soll
    char str_profil_answer;
    do {
        cout << "Möchten Sie außerdem das Strömungsprofil berechnen? [Y/N]";
        cin >> str_profil_answer;
    }
    while((str_profil_answer != 'Y') && (str_profil_answer != 'N'));

    // Falls gewünscht, Strömungsprofil berechnen
    if(str_profil_answer == 'Y'){
        // Abfrage, an welcher Stelle x berechnet werden soll.
        double str_profil_x;
        do {
            cout << endl << "Bitte geben Sie eine Stelle x im Rohr an: ";
            cin >> str_profil_x;
        }while((str_profil_x < 0) || (str_profil_x > rohr.get_laenge()));

        // Auflösung festlegen: Mit n Datenpunkten über Radius iterieren
        double str_profil_n = 20;

        // Enthält Wert des Radius, dessen Geschwindigkeit berechnet werden soll
        double str_profil_r;

        // Berechnung ausführen
        for(int i = 0; i < str_profil_n; i++){
            str_profil_r = rohr.get_radius()*i/str_profil_n;
            cout << "r[" << str_profil_r << "]=" << rohrstroemung.get_stroemung(str_profil_r, str_profil_x) << " m/s" << endl;
        }
    }


}

void run_tests(){
    RUNTEST
}
