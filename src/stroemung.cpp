#include "math.h"
#include "stroemung.h"
#include "rohr.h"
#include "fluid.h"
#include "dateneingabe.h"

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
    double m = this->fluid.get_massenstrom();
    double rho = this->fluid.get_dichte();

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

double Rohrstroemung::get_bauart(){
    return this->rohr.get_kA() / this->fluid.get_cp_strom();
}

double Rohrstroemung::get_epsilon(){
    return 1 - exp((-1) * this->get_bauart());
    //return 1 - pow(exp(1), - this->get_bauart());
}

double Rohrstroemung::get_temp(double t_aussen){
    return this->fluid.get_t_ein() - this->get_epsilon() * (this->fluid.get_t_ein() - t_aussen); // t_austritt = t_ein - epsiolon * tempdifferenz
}

double Rohrstroemung::get_pressure(double x){
    //double vstart = this->get_speed(0);
    //double vpoint = this->get_speed(x);

    //double p = this->get_startpressure(); //NOCH NICHT IMPLEMENTIERT!
    double p = 5; // auf konsante setzen, da noch nicht implementiert
    double lambda = this->get_lambda();
    double d = 2 * rohr.get_radius();
    double rho = fluid.get_dichte();
    double v = this->get_speed();

    return p-((lambda*x*rho*v*v)/(d*2));
}

//Berechnung des Strömungprofils
