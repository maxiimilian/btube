#include <math.h>
#include "rohr.h"
#include <stdexcept>

Rohr::Rohr(){}
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
    return M_PI*pow(this->get_radius(), 2);
}
double Rohr::get_querschnitt(double x){
    return M_PI*pow(this->get_radius(x), 2);
}

double Rohr::get_laenge(){
    return this->laenge;
}

double Rohr::get_alpha_innen(){
    return this->alpha_innen;
}

double Rohr::get_aplha_aussen(){
    return this->alpha_aussen;
}


/*!
 * \brief Berechenet den Wärmdurchgangskoeffzient
 *
 * \warning Anderer Ansatz: Es werden keine Werte der Funktion übergeben sondern in der Funktion get-Funktionen aufgerufen
 * \sa Fluid::set_cp_strom
 */
double Rohr::get_kA(){
    return this->kA = 2 * M_PI * this->get_radius() * this->get_laenge() * (this->get_alpha_innen() + this->get_aplha_aussen()); //2*Pi*r*L(alpha_innen+alpha_außen)
}

double Rohr::get_kA(double x){
    /*!
     * berechnet den Wert von kA an einer bestimmten Stelle.
     * Kann überschrieben werden, um den Radius als kA=f(x) auszudrücken.
     */

    //Prüfe ob Ort x innerhalb des Rohres liegt
    if ( x <= this->get_laenge()){
    return this->kA = 2 * M_PI * this->get_radius() * x * (this->get_alpha_innen() + this->get_aplha_aussen()); //2*Pi*r*x(alpha_innen+alpha_außen)
    }

    else {
        throw std::out_of_range("Ort x muss im Rohr liegen und damit kleiner als die Länge sein!");
    }
}

void Rohr::set_alpha_innen(double alpha_innen){
    this->alpha_innen = alpha_innen;
}

void Rohr::set_aplha_aussen(double alpha_aussen){
    this->alpha_aussen = alpha_aussen;
}

