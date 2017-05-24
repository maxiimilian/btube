#include "fluid.h"
#include <stdexcept>

Fluid::Fluid(){}
Fluid::Fluid(double dichte, double nue){
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
}

double Fluid::get_dichte(){
    return this->dichte;
}

double Fluid::get_massenstrom(){
    /// \todo: prüfen ob gesetzt
    return this->massenstrom;
}

double Fluid::get_nue(){
    return this->nue;
}

void Fluid::set_massenstrom(double massenstrom){
    this->massenstrom = massenstrom;
}
