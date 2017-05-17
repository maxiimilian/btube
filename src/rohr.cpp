#include <math.h>
#include "rohr.h"
#include <stdexcept>

Rohr::Rohr(){};
Rohr::Rohr(double l, double r){
    // Prüfen, ob Länge größer als Null ist
    if(l > 0){
        this->laenge = l;
    }
    else{
        throw std::out_of_range("Rohrlänge muss positiv und größer Null sein!");
    }

    // Prüfen, ob Radius größer Null ist
    if(r > 0){
        this->radius = r;
    }
    else {
        throw std::out_of_range("Rohrradius muss positiv und größer Null sein!");
    }
}

double Rohr::get_radius(){
    // gibt den Wert des Radius-Attributs zurück
    return this->radius;
}

double Rohr::get_radius(double x){
    /*! 
     * gibt den Wert des Radius an einer bestimmten Stelle zurück.
     * Kann überschrieben werden, um den Radius als r=f(x) auszudrücken.
     */
    // Prüfen, ob r(x) definiert ist.
    if(x <= this->laenge){
        return this->radius;
    }
    else {
        throw std::out_of_range("Der übergebene x-Wert liegt außerhalb des Rohrs");
    }
}

double Rohr::get_querschnitt(){
    return 3.14*pow(this->get_radius(), 2);
}
double Rohr::get_querschnitt(double x){
    return 3.14*pow(this->get_radius(x), 2);
}
