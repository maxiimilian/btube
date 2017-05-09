#include <math.h>
#include "rohr.h"

Rohr::Rohr(double l, double r){
    /* Rohr-Konstruktor: Erstellt ein Rohr mit Länge und Radius */
    this->laenge = l;
    this->radius = r;
}

double Rohr::get_querschnitt(double x=0){
    return 3.14*pow(this->radius, 2);
}
