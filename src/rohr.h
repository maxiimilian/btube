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

        /// Rohrrauheit k_s [m]
        double k_s;

        /// Konvektionswiderstand für Innenseite (Watt pro Quadratmeter und Kelvin)
        double alpha_innen;

        /// Konevktionswiderstand für Außenseite (Watt pro Quadratmeter und Kelvin)
        double alpha_aussen;

        /// Wrämedurchgangskoeffizient [Watt pro Kelvin]
        double kA;

        /// Aussentemperatur [Celcius oder Kelvin]
        double t_aussen;

        /// Eingangsdruck
        double p_ein;



    public:
        Rohr(double l, double r, double k_s);

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

        /// Gibt Konvektionswiderstand auf der Innenseite zurück
        double get_alpha_innen();

        /// Gibt Konvektionswiderstand auf der Außenseite zurück
        double get_alpha_aussen();

        /// Berechnet Wärmedurchgangskoeffizient
        double get_kA();

        /*!
         * \brief Berechnet Wärmedurchgangskoeffizient an der Stelle x und speichert ihn auch unter kA
         *
         * \warning Diese Funktion überschreiben, um kA=f(x) zu realisieren.
         */
        double get_kA(double x);

        ///Gibt Aussentemperatur zurück
        double get_t_aussen();

        /// Setzt Wert für Konvektionswiderstand auf der Außenseite
        void set_alpha_aussen(double alpha_aussen);

        /// Setzt Wert für Konvektionswiderstand auf der Innenseite
        void set_alpha_innen(double alpha_innen);

        ///Setzt Wert für Aussentemperatur
        void set_t_aussen(double t_aussen);

        /// Gibt Rohrrauheitswert aus
        double get_k_s();

        /// Gibt Startdruck zurück
        double get_startpressure();
};

#endif 
