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
};

#endif 
