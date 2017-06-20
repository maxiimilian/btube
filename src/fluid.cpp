#include "fluid.h"
#include <stdexcept>

/***************
 * KONSTRUKTOR *
 ***************/
Fluid::Fluid(double dichte, double nue, double cp){
    // Validieren, dass Dichte und Viskosität größer Null sind
    if(nue > 0){
        this->nue = nue;
    }
    else {
        throw std::out_of_range("Die Viskosität muss größer Null sein!");
    }

    if(dichte > 0){
        this->dichte = dichte;
    }
    else {
        throw std::out_of_range("Die Dichte muss größer Null sein!");
    }

    if(cp > 0){
        this->cp = cp;
    }
    else {
        throw std::out_of_range("Die Wärmekapazität muss größer Null sein!");
    }

}

/***************
 * GET methods *
 ***************/
/// Dichte ausgeben
double Fluid::get_dichte(){
    return this->dichte;
}

/// Massenstrom ausgeben
double Fluid::get_massenstrom(){
    return this->massenstrom;
}

/// isobare spezifische Wärmekapazität ausgeben
double Fluid::get_cp(){
    return this->cp;
}

/// kinematische Viskosität ausgeben
double Fluid::get_nue(){
    return this->nue;
}

/// Eintrittstemperatur ausgeben
double Fluid::get_t_ein(){
    return this->t_ein;
}

/// dynamische Viskosität ausgeben
double Fluid::get_my(){
    return nue*dichte;
}

/// cp-Strom ausgeben
double  Fluid::get_cp_strom(){
    return this->cp_strom = this->get_cp() * this->get_massenstrom();
}

/***************
 * SET methods *
 ***************/
/// Massenstrom setzen
void Fluid::set_massenstrom(double massenstrom){
    this->massenstrom = massenstrom;
}

/// Eintrittstemperatur setzen
void Fluid::set_t_ein(double t_ein){
    this->t_ein = t_ein;
}
