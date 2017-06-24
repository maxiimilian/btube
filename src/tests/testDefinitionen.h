#ifndef TESTDEFINITIONEN_H
#define TESTDEFINITIONEN_H

#include <iostream>

#ifdef TEST
#include "test.h"

#include <math.h>

#include "../fluid.h"
#include "../rohr.h"
#include "../stroemung.h"


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

#endif // TEST


void runTests(){
#ifdef TEST  // Nicht modifizieren
	APITest::printTestStartHeader(); // Nicht modifizieren

	// Hier sollen die eigenen Tests hinzugefuegt werden
    test_lambda_Berechnung();
    test_Temperatur_Berechnung();

	APITest::printTestEndFooter(); // Nicht modifizieren
#endif //TEST // Nicht modifizieren
}


#ifdef TEST  // Nicht modifizieren
	#define RUNTEST runTests();
#else
	#define RUNTEST
#endif


#endif //TESTDEFINITIONEN_H
