#include "rohr.h"
#include "fluid.h"

#ifndef STROEMUNG_H
#define STROEMUNG_H

/*! 
 * \brief Beschriebt eine Rohrströmung
 *
 * Benötigt dazu Objekte von Rohr und Fluid.
 * 
 * \warning Es werden keine kompressiblen Fluide oder Ablösungen 
 * und Einlaufstörungen am Ein- und Ausgang des Rohrs berücksichtigt.
 *
 * \note Zur Laufzeitoptimierung werden dieser Funktion nur Pointer auf Rohr und Fluid übergeben!
 */
class Rohrstroemung
{
    private:
        Rohr* rohr;
        Fluid* fluid;

        double druckverlauf[2][101]={{0.0},{0.0}};

    public:
        /***************
         * Konstruktor *
         ***************/
        Rohrstroemung(Rohr* rohr, Fluid* fluid);

        /***************
         * GET methods *
         ***************/
        /// Reynoldszahl des Member-Fluids berechnen (u*d/nue)
        double get_Re();                                // Simon Thel

        /// Rohrreibungszahl Lambda berechnen, in Abhängigkeit von Re \sa get_Re()
        double get_lambda();

        /// Berechnung der Fluidgeschwindigkeit durch den Massenstorm
        double get_speed();                             // Simon Thel

        /// Berechnet Bauartszahl
        double get_bauart();                            // Simon Thel

        /// Gibt Leistungsgröße zurück
        double get_epsilon();                           // Simon Thel

        /// Berechnet Austrittstemperatur
        double get_temp(double x);                      // Simon Thel

        /// Berechnung des Drucks an der Stelle x
        double get_pressure(double x);

        /// Berechnet Temperatur an der Stelle x
        double get_temp();                              // Simon Thel

        /// Berechnet Epsilon an  der Stelle x
        double get_epsilon(double x);                   // Simon Thel

        /// Berechnet die Bauart an der Stelle x
        double get_bauart(double x);                    // Simon Thel

        /// Berechnung des Strömungsprofils
        double get_stroemung(double r, double x);

        /// Gibt letzten Druckwert zurück (für Testing)
        double get_druckverlauffortest();

        /***************
         * SET methods *
         ***************/
        /// Ausfüllen des Druckverlauf-Arrays
        void set_druckverlauf();

        /// Eintragen des Druckverlauf-Arrays in Textdatei
        void print_druckverlauf();
};

/*!
 * \brief The LambdaTurbulentGlattSolver class
 *
 * Löst die Gleichung für den Rohrreibungsbeiwert Lambda,
 * für Re > 100000 und hydraulisch glatte Rohre numerisch.
 */
class LambdaTurbulentGlattSolver{
    private:
        double eq_left(double x, double y);
        double eq_right(double x, double y);
    public:
        double get_lambda(double Re);
};

#endif // STROEMUNG_H
