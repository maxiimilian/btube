#include "fluid.h"
#include <stdexcept>

Fluid::Fluid(){}
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

double Fluid::get_dichte(){
    return this->dichte;
}

double Fluid::get_massenstrom(){
    /// \todo: prüfen ob gesetzt
    return this->massenstrom;
}

double Fluid::get_cp(){
    return this->cp;
}

double Fluid::get_nue(){
    return this->nue;
}

double Fluid::get_t_ein(){
    return this->t_ein;
}

void Fluid::set_massenstrom(double massenstrom){
    this->massenstrom = massenstrom;
}

/*!
 * \brief Berechnet den Wärmekapazitätsstrom.
 *
 * \warning Ist es wirklich nötig die Vairablen der Funktion zu übergeben oder ist auch ein anderer Ansatz über enstprechende get-Funktionen möglich?
 * \sa Rohr::set_kA
 */
double  Fluid::get_cp_strom(){
    double cp = this->get_cp();
    double m = this->get_massenstrom();
    double w = cp*m;
    cp_strom = w;

    return this->cp_strom;
}

void Fluid::set_t_ein(double t_ein){
    this->t_ein = t_ein;
}
