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
    double rho = this->fluid.get_dichte();
    double m = this->fluid.get_massenstrom(); //Funktionen sind noch nicht definiert

    return m/(A*rho);
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

double Rohrstroemung::get_pressure(double x){
    //double vstart = this->get_speed(0);
    //double vpoint = this->get_speed(x);

    double p = this->get_startpressure(); //NOCH NICHT IMPLEMENTIERT!
    double lambda = this->get_lambda();
    double r = rohr.get_radius();
    double d = 2*r;
    double rho = fluid.get_dichte();
    double v = this->get_speed();

    return p-((lambda*x*rho*v*v)/(d*2));
}
