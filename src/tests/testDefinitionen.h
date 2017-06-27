#ifndef TESTDEFINITIONEN_H
#define TESTDEFINITIONEN_H

#include <iostream>
#include <cstring>

#ifdef TEST
#include "test.h"

#include <math.h>

#include "../fluid.h"
#include "../rohr.h"
#include "../stroemung.h"
#include "../cli.h"


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
#endif // TEST


void runTests(){
#ifdef TEST  // Nicht modifizieren
	APITest::printTestStartHeader(); // Nicht modifizieren

	// Hier sollen die eigenen Tests hinzugefuegt werden
    test_lambda_Berechnung();
    test_cli();

	APITest::printTestEndFooter(); // Nicht modifizieren
#endif //TEST // Nicht modifizieren
}


#ifdef TEST  // Nicht modifizieren
	#define RUNTEST runTests();
#else
	#define RUNTEST
#endif


#endif //TESTDEFINITIONEN_H
