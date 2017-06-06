#ifndef TESTDEFINITIONEN_H
#define TESTDEFINITIONEN_H

#include <iostream>

#ifdef TEST
#include "test.h"

#include <math.h>

#include "../fluid.h"
#include "../rohr.h"
#include "../stroemung.h"

/// Testfunktion der Berechnung der Reynoldszahl
void test_Re_Berechnung(){
    bool testResult = false;
    
    // Rohr mit Länge und Radius
    Rohr rohr(100, 15);

    // Fluid mit Dichte, Viskosität und Massenstrom
    // cp = 1.4 wird in diesem Test aktuell nicht verwendet,
    // wird aber vollständigkeitshalber übergeben
    Fluid fluid(123, 5.43e-6, 1.4);
    fluid.set_massenstrom(50);

    // Rohrströmung
    Rohrstroemung rohrstroemung(rohr, fluid);

    // Prüfen, ob sich Berechnung und Taschenrechnerwert um max. 0.5 unterscheiden
    if(fabs(rohrstroemung.get_Re()-10590.895)<=0.5){
        testResult = true; 
    }

    APITest::printTestResult(testResult, 
            "Reynoldszahl", 
            "Maximilian Pierzyna",
            "Berechnung der Reynoldszahl",
            "rohr.cpp, fluid.cpp, stroemung.cpp");
}

/// Testfunktion des Rohrreibungsbeiwerts
void test_lambda_Berechnung(){
    bool testResult = false;

    LambdaTurbulentGlattSolver ltgs;
    if(fabs(ltgs.get_lambda(1000000)-0.0116465) < 1e-7){
        testResult = true;
    };

    APITest::printTestResult(testResult, "Rohrreibungsbeiwert", "Maximilian Pierzyna");
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
