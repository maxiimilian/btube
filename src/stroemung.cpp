#include "math.h"
#include "stroemung.h"
#include "rohr.h"
#include "fluid.h"

Rohrstroemung::Rohrstroemung(Rohr rohr, Fluid fluid){
    // Rohr und Fluid mit der Rohrströmung verbinden
    this->rohr = rohr;
    this->fluid = fluid;
}

double Rohrstroemung::get_Re(){
    double u = this->get_speed();
    double nue = this->fluid.get_nue();
    double l = this->rohr.get_laenge();

    return (u*l)/nue;
}

double Rohrstroemung::get_speed(){

    double A = this->rohr.get_querschnitt();
    double roh = this->fluid.get_dichte();
    double m = this->fluid.get_massenstrom(); //Funktionen sind noch nicht definiert

    return m/(A*roh);
}

double Rohrstroemung::get_lambda(){
    double Re = get_Re();

    if(Re < 2300){
        // Laminare Strömung, Gesetz von Hagen-Poiseuille
        return 64/Re;
    }
    if(Re < 100000){
        // turbulent, aber hydraulisch glatt
        return 0.3164/pow(Re, 0.25); 
    }

    // Fallback / Schätzung
    return 0.03;
}
