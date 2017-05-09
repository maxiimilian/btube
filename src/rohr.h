#ifndef ROHR_H_
#define ROHR_H_

class Rohr 
{
    private:
        /* Eigenschaften des Rohrs definieren */
        double laenge;
        double radius;

    public:
        /* Funktionen des Rohrs definieren */
        // Konstruktor wird bei Initialisierung aufgerufen
        Rohr(const double, const double);

        // Gibt Querschnittsfläche zurück
        double get_querschnitt(const double x);
};

#endif 
