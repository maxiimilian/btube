#include "fluid.h"

Fluid::Fluid(){}
Fluid::Fluid(double dichte, double massenstrom, double nue){}

double Fluid::get_dichte(){
    return this->dichte;
}

double Fluid::get_massenstrom(){
    return this->massenstrom;
}

double Fluid::get_nue(){
    return this->nue;
}

