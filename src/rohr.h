#ifndef ROHR_H
#define ROHR_H

class Rohr 
{
    private:
        /* Eigenschaften des Rohrs definieren */
        double laenge;
        double radius;

    public:
        /* Funktionen des Rohrs definieren */
        // Konstruktor wird bei Initialisierung aufgerufen
        Rohr(const double l, const double r);

        // Gibt Querschnittsfläche zurück
        double get_querschnitt(const double x);
};

#endif 
