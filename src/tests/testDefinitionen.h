#ifndef TESTDEFINITIONEN_H
#define TESTDEFINITIONEN_H

#include <iostream>
#include <cstring>

#ifdef TEST
#include "test.h"

#include <math.h>
#include <QDialog>

#include "../fluid.h"
#include "../rohr.h"
#include "../stroemung.h"
#include "../cli.h"
#include "../plotter.h"
#include "../dateneingabe.h"


/*!
 * \brief Testfunktion des Rohrreibungsbeiwerts
 *
 * Diese Funktion testet die verschiedenen Fallunterscheidungen der
 * Rohrreibungsbeiwertberechnung. Damit werden impliziet auch
 * - der numerische Solver
 * - die Funktion get_speed()
 * - die Funktion get_Re()
 * getestet.
 *
 * Der Rechenweg der Referenzwerte befindet sich im Wiki bei der
 * entsprechenden Testdokumentation! (Scan der Rechenschritte)
 */
void test_lambda_Berechnung(){
    bool testResult = true;

    // Fluid definieren
    Fluid wasser(1000, 1e-6, 4180);
    // Rohr definieren
    Rohr rohr(100, 0.5, 100e-6);
    // Rohrströmung definieren
    Rohrstroemung str_wasser(&rohr, &wasser);

    /*
     * Test für laminare Rohrströmung mit Wasser (Re = 1273)
     */
    wasser.set_massenstrom(1);
    if(fabs(str_wasser.get_lambda()-0.05026548) > 1e-7){
        testResult = false;
    }

    /*
     * Test für turbulente Strömung im hydr. glatten Rohr, Re < 10e5
     */
    wasser.set_massenstrom(10);
    if(fabs(str_wasser.get_lambda()-0.02978578) > 1e-7){
        testResult = false;
    }

    /*
     * Test für turbulente Strömung im rauen Rohr (Übergangsberich wird vernachlässigt!!)
     */
    wasser.set_massenstrom(100);
    if(fabs(str_wasser.get_lambda()-0.01197577) > 1e-7){
        testResult = false;
    }

    /*
     * Test für turbulente Strömung im hydr. glatten Rohr, Re > 10e5
     * Rohrrauheit muss angepasst werden, da k_s_zul für gewählten Massenstrom bei etwa 78e-6 liegt.
     * Hier wird der numerische Solver getestet! Der Vergleichswert stammt von WolframAlpha
     */
    rohr = Rohr(100, 0.5, 50e-6);
    if(fabs(str_wasser.get_lambda() - 0.0171176) > 1e-7){
        testResult = false;
    }

    APITest::printTestResult(testResult,
                             "Rohrreibungsbeiwert",
                             "Maximilian Pierzyna",
                             "Berechnung des Rohrreibungsbeiwerts und der jeweiligen nötigen Fallunterscheidungen",
                             "stroemung.cpp, (rohr.cpp, fluid.cpp implizit)");
}

/*!
 * \brief Testfunktion der Konsolenausgabe
 *
 * Testet, ob die interaktive Konsole gestartet wird,
 * wenn dem Programm das Argument 'cli' in der Shell übergeben wird.
 */
void test_cli(){
    bool testResult = true;

    // Globalen Ausführungspfad aufrufen und 'cli' anhängen
    extern std::string run_path;
    std::string run_path_cli = run_path + " cli";
    const char* run_path_cli_char = run_path_cli.c_str();

    // Einen Dateihandler und eine 8 Bit Buffer deklarieren
    FILE *in;
    char buff[8];

    // Das Programm ruft sich selbst mit Parameter 'cli' auf und schreibt
    // den Output in den Dateihandler in
    if(!(in = popen(run_path_cli_char, "r"))){
        testResult = false;
    }
    else {
        // Die ersten 8 Bit der stdout-Ausgabe in den buffer lesen
        fgets(buff, sizeof(buff), in);

        /* File handle kann hier nicht geschlossen werden, da der Test sonst blockiert wird.
         * Dies liegt daran, dass der Prozess sich selbst aufruft. Der Handle bleibt daher offen 
         * und wird zum Laufzeitende automatisch geschlossen
         *
         * pclose(in);
         */

        // Test nicht erfolgreich, falls im ersten Buffer KEIN * vorkommt! 
        if(strchr(buff, '*') == NULL){
            testResult = false;
        }
    }

    // Testergebnis ausgeben
    APITest::printTestResult(testResult,
                             "CLI",
                             "Maximilian Pierzyna",
                             "CLI wird mit Shell-Argmument gestartet",
                             "cli.cpp, main.cpp");
}

/*!
 * \brief Testfunktion des Temperaturverlaufs
 *
 * Diese Funktion testet die Funktion get_temp() der Klasse Rohrstroemung. Damit werden
 * indirekt auch die Funktionen für die Berechnung der Werte des angenommen Wärmetauschers
 * sowie die Berechungsfunktionen für den Wärmekapazitätsstroms
 *
 * Der Rechenweg der Referenzwerte befindet sich im Wiki bei der
 * entsprechenden Testdokumentation! (Scan der Rechenschritte)
 */
void test_Temperatur_Berechnung(){
    bool testResult = true;

    //Fluid erstellen mit Fluid-Konstruktor
    Fluid test_fluid(1000, 1e-6, 5000);
    //Rohr erstellen mit Rohr-Konstruktor
    Rohr test_rohr(50, 1, 100e-6);
    //Strömung erstellen mit Rohrkonstruktor
    Rohrstroemung test_stroemung(&test_rohr, &test_fluid);

    //Allgemeine Rohr und Fluid-Parameter setzen
    test_fluid.set_massenstrom(1);
    test_rohr.set_alpha_innen(3);
    test_rohr.set_alpha_aussen(2);

    /*
     * Fall 1: Fluid wird von der Umgebung abgekühlt.
     */
     test_fluid.set_t_ein(400);
     test_rohr.set_t_aussen(200);

     //fabs-Funktion gibt den Betrag der Differenz wieder und erleichtert so die Fallunterscheidung
     if(fabs(test_stroemung.get_temp()-346.080536) > 1e-5){
          testResult = false;
     }

    /*
     * Fall 2: Fluid wird von der Umgebung erwärmt.
     */
     test_fluid.set_t_ein(200);
     test_rohr.set_t_aussen(400);

     if(fabs(test_stroemung.get_temp()-253.919462) > 1e-5){
          testResult = false;
     }

    /*
     * Fall3: Fluid und Umgebung haben die gleiche Temperatur. Somit ändert das Fluid seine Temperatur nicht.
     */
     test_fluid.set_t_ein(300);
     test_rohr.set_t_aussen(300);

     if(fabs(test_stroemung.get_temp()-300.0) > 1e-5){
          testResult = false;
     }

     APITest::printTestResult(testResult,
                              "Fluidtemperatur",
                              "Simon Thel",
                              "Fluidtemperatur mit 3 verschiedenen Fällen: Abkühlung, Erwärmung und gleiche Temperaturen",
                              "stroemung.cpp, (rohr.cpp, fluid.cpp implizit)");
}

/*!
 * \brief Testfunktion des Werteplotters
 *
 * Diese Funktion überprüft ob die Plotterfunktion eine korrekte Anzahl an Datenpunkten erstellt. Wenn die
 * Funktion einen Wert zurückgibt, zeigt dies ebenfalls, dass die Funktion vollständig ausgeführt worden ist.
 */
void test_Plotter(){
    bool testResult = false;

    //Fluid definieren
    Fluid test_fluid (1, 1, 1);
    //Rohr definieren
    Rohr test_rohr(1, 1, 1e-5);
    //Plotter defnieren
    Plotter test_plotter;

    if(test_plotter.erstellePlot(test_rohr, test_fluid) == 40202){
       testResult = true;
    }

    APITest::printTestResult(testResult,
                             "Plotter",
                             "Simon Thel",
                             "Erstellung der korrekten Anzahl an Datenpunkten; komplettes Durchlaufen der Plotterfunktion",
                             "plotter.cpp");
}

#endif // TEST


void runTests(){
#ifdef TEST  // Nicht modifizieren
	APITest::printTestStartHeader(); // Nicht modifizieren

	// Hier sollen die eigenen Tests hinzugefuegt werden
    test_lambda_Berechnung();
    test_cli();
    test_Temperatur_Berechnung();
    test_Plotter();

	APITest::printTestEndFooter(); // Nicht modifizieren
#endif //TEST // Nicht modifizieren
}


#ifdef TEST  // Nicht modifizieren
	#define RUNTEST runTests();
#else
	#define RUNTEST
#endif

#endif
