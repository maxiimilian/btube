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
                             "stroemung.cpp");
}

#endif // TEST


void runTests(){
#ifdef TEST  // Nicht modifizieren
	APITest::printTestStartHeader(); // Nicht modifizieren

	// Hier sollen die eigenen Tests hinzugefuegt werden
    test_Re_Berechnung();
    test_lambda_Berechnung();

	APITest::printTestEndFooter(); // Nicht modifizieren
#endif //TEST // Nicht modifizieren
}


#ifdef TEST  // Nicht modifizieren
	#define RUNTEST runTests();
#else
	#define RUNTEST
#endif


#endif //TESTDEFINITIONEN_H
