#ifndef ROHR_H
#define ROHR_H

/*!
 * \brief Stellt ein Rohrbauteil zur Verfügung
 */
class Rohr 
{
    private:
        /// Rohrlänge in m
        double laenge;

        /// Rohrradius in m
        double radius;

        /// Konvektionswiderstand für Innenseite (Watt pro Quadratmeter und Kelvin)
        double alpha_innen;

        /// Konevktionswiderstand für Außenseite (Watt pro Quadratmeter und Kelvin)
        double alpha_außen;

        ///Wrämedurchgangskoeffizient (Watt pro Kelvin)
        double kA;


    public:
        Rohr();
        Rohr(double l, double r);

        /// Gibt Querschnittsfläche
        double get_querschnitt();

        /*! 
         * \brief Gibt den Querschnitt an der Stelle x zurück.
         *
         * \warning Basiert auf get_radius, daher wird r=f(x) hier 
         * automatisch berücksichtigt. Nicht doppelt überschreiben!
         * \sa Rohr::get_radius(double x)
         */
        double get_querschnitt(double x);

        /// Gibt Radius zurück
        double get_radius();
        
        /*!
         * \brief Gibt Radius an der Stelle x zurück.
         *
         * Diese Funktion überschreiben, um r=f(x) zu realisieren
         */
        double get_radius(double x);

        /// Gibt Länge zurück
        double get_laenge();

        /// Gibt Bauart zurück
        double get_bauart();

        /// Gibt Konvektionswiderstand auf der Innenseite zurück
        double get_alpha_innen();

        /// Gibt Konvektionswiderstand auf der Außenseite zurück
        double get_aplha_außen();

        /// Gibt Wärmedurchgangskoeffizient zurück
        double get_kA();

        /// Berechnet Wärmedurchgangskoeffizient
        void set_kA();

        /// Berechnet Leistungszahl
        void set_epsilon();


};

#endif 
