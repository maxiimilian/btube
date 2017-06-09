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
 */
class Rohrstroemung
{
    private:
        Rohr rohr;
        Fluid fluid;

        double druckverlauf[2][100]={{0.0},{0.0}};

    public:
        // Konstruktor
        Rohrstroemung(Rohr rohr, Fluid fluid);

        /// Reynoldszahl des Member-Fluids berechnen
        double get_Re();

        /// Rohrreibungszahl Lambda berechnen, in Abhängigkeit von Re \sa get_Re()
        double get_lambda();

        /// Berechnung der Fluidgeschwindigkeit durch den Massenstorm
        double get_speed();

        /// Berechnet Bauartszahl
        double get_bauart();

        /// Gibt Leistungsgröße zurück
        double get_epsilon();

        /// Berechnet Austrittstemperatur
        double get_temp(double x);

        /// Gibt Startdruck zurück
        double get_startpressure();

        /// Berechnung des Drucks an der Stelle x
        double get_pressure(double x);

        /// Berechnet Temperatur an der Stelle x
        double get_temp();

        /// Berechnet Epsilon an  der Stelle x
        double get_epsilon(double x);

        /// Berechnet die Bauart an der Stelle x
        double get_bauart(double x);

        /// Ausfüllen des Druckverlauf-Arrays
        void ausgabe();
};


#endif // STROEMUNG_H
