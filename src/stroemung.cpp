#include "math.h"
#include "stroemung.h"
#include "rohr.h"
#include "fluid.h"
#include "dateneingabe.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/***************
 * Konstruktor *
 ***************/
Rohrstroemung::Rohrstroemung(Rohr* rohr, Fluid* fluid){
    // Rohr und Fluid mit der Rohrströmung verbinden
    this->rohr = rohr;
    this->fluid = fluid;
}

/***************
 * GET methods *
 ***************/
double Rohrstroemung::get_Re(){
    // Re_D zurückgeben
    return this->get_speed()*2*this->rohr->get_radius()/this->fluid->get_nue();
}

double Rohrstroemung::get_druckverlauffortest(){
    return this->druckverlauf[1][100];
}

double Rohrstroemung::get_speed(){

    double A = this->rohr->get_querschnitt();
    double m = this->fluid->get_massenstrom();
    double rho = this->fluid->get_dichte();

    return m/(A*rho);
}

double Rohrstroemung::get_lambda(){
    double Re = get_Re();

    if(Re < 2300){
        // Laminare Strömung, Gesetz von Hagen-Poiseuille (1)
        return 64/Re;
    }
    // Zulässige Rohrrauheit, für die noch die hydraulisch glatte Strömung gilt
    double k_s_zul = 10*this->fluid->get_nue()/this->get_speed();

    if(this->rohr->get_k_s() <= k_s_zul){
        // hydraulisch glatt

        if(Re < 1e5){
            // turbulent, aber hydraulisch glatt (2)
            return 0.3164/pow(Re, 0.25);
        }

        // Re > 1e5 (3)
        LambdaTurbulentGlattSolver ltgs;
        return ltgs.get_lambda(Re);
    }
    else {
        // raue Strömung (5)
        return pow(1/(1.74-2*log10(this->rohr->get_k_s()/this->rohr->get_radius())),2);
    }

    // Fallback / Schätzung
    return 0.03;
}

double Rohrstroemung::get_bauart(){
    return this->rohr->get_kA() / this->fluid->get_cp_strom();
}

double Rohrstroemung::get_bauart(double x){
    //Prüfe ob Ort x innerhalb des Rohres liegt
    if ( x <= this->rohr->get_laenge()){
        return this->rohr->get_kA(x) / this->fluid->get_cp_strom();
    }
    
    else {
        throw std::out_of_range("Ort x muss im Rohr liegen und damit kleiner als die Länge sein!");
    }
}

double Rohrstroemung::get_epsilon(){
    return 1 - exp((-1) * this->get_bauart());
}

double Rohrstroemung::get_epsilon(double x){
    //Prüfe ob Ort x innerhalb des Rohres liegt
    if ( x <= this->rohr->get_laenge()){
        return 1 - exp( (-1) * this->get_bauart(x));
    }
    
    else {
        throw std::out_of_range("Ort x muss im Rohr liegen und damit kleiner als die Länge sein!");
    }
}

double Rohrstroemung::get_temp(){
    return this->temp = this->fluid->get_t_ein() + this->get_epsilon() * (this->rohr->get_t_aussen() - this->fluid->get_t_ein()); // t_austritt = t_ein - epsiolon * tempdifferenz
}

double Rohrstroemung::get_temp(double x){
    //Prüfe ob Ort x innerhalb des Rohres liegt
    if ( x <= this->rohr->get_laenge() ){
        return this->fluid->get_t_ein() + this->get_epsilon(x) * (this->rohr->get_t_aussen() - this->fluid->get_t_ein()); // t_austritt = t_ein - epsiolon * tempdifferenz
    }
    
    else {
        throw std::out_of_range("Ort x muss im Rohr liegen und damit kleiner als die Länge sein!");
    }
}

//Berechnung des noch vorhandenen Drucks nach Entfernung x
double Rohrstroemung::get_pressure(double x){
    //double vstart = this->get_speed(0);
    //double vpoint = this->get_speed(x);

    double p = rohr->get_startpressure();
    double lambda = this->get_lambda();
    double d = 2 * rohr->get_radius();
    double rho = fluid->get_dichte();
    double v = this->get_speed();

    return p-((lambda*x*rho*v*v)/(d*2))*0.00001;  //Berechnung des Enddrucks nach Strecke x mit Umrechnung [N/m²] in [bar]
}

//Berechnung des Strömungprofils [laminare Strömung (Hagen-Poisseuille'sche Rohrströmung)]
double Rohrstroemung::get_stroemung(double r, double x){
    double my = this->fluid->get_my();
    double radius = this->rohr->get_radius();
    double l = this->rohr->get_laenge();

    // Gemittelter Druckgradient über gesamtes Rohr
    double dp_dx = (this->get_pressure(l)-this->get_pressure(0))/l;

    // Geschwindigkeit u(r,x) berechnen
    return -1/(4*my)*dp_dx*(pow(radius,2)-pow(r-radius,2));
}

/***************
 * SET methods *
 ***************/

//Füllen des Arrays für die Werte des Druckverlaufs
void Rohrstroemung::set_druckverlauf(){
    double x = rohr->get_laenge() / 100;                    //Stückelung in 100 Teile
    this->druckverlauf[0][0] = 0;
    this->druckverlauf[1][0] = rohr->get_startpressure();
    for(int i=1; i<101; i++){                               //Array wird gefüllt
        this->druckverlauf[0][i] = i*x;
        this->druckverlauf[1][i] = get_pressure(i*x);
    }
}

//Ausgabe der Werte des Druckverlaufs in Form einer Wertetabelle in einer Textdatei
void Rohrstroemung::print_druckverlauf(){
    ofstream tabellenausgabe;
    tabellenausgabe.open("Druckverlauf.txt");
    tabellenausgabe << setw(10) << right << "x-Wert [m]" << " | Druck [bar]" << endl;
    for (int i=0; i<101; i++){                                                             //Textdatei wird geschrieben
    tabellenausgabe << setw(10) << right << this->druckverlauf[0][i] << " | " << this->druckverlauf[1][i] << endl;
    }
    tabellenausgabe.close();
}

/*****************************
 * Numeric Solver for Lambda *
 *****************************/
/// Solver für Lambda bei hydraulisch glatten, turbulenten Strömungen
double LambdaTurbulentGlattSolver::get_lambda(double Re)
{
    double y_ceil = 0.03; // Wird nicht größer werden, da konvergiert
    double y_floor = 0; // Gleichung konvergiert gegen Null für Re->inf

    double r = 0; // aktuelle rechte Seite der Gleichung
    double l = 0; // aktuelle linke Seite der Gleichung
    double y = 0; // aktuelles y = lambda
    double epsilon = 1e-7; // Genauigkeit

    do {
        y = y_floor + (y_ceil - y_floor) / 2;
        r = this->eq_right(Re, y);
        l = this->eq_left(Re, y);

        // Linke und rechte Seite der Gleichung vergleichen
        if((r-l) > 0){
            // Wenn > 0, ceiling setzen
            y_ceil = y;
        }
        else {
            // Wenn < 0, floor setzen
            y_floor = y;
        }
    }
    while(fabs(r-l) > epsilon);

    return y;
}

/// Enthält die linke Seite der zu lösenden Gleichung
double LambdaTurbulentGlattSolver::eq_left(double x, double y){
    return 1/sqrt(y);
}

/// Enthält die rechte Seite der zu lösenden Gleichung
double LambdaTurbulentGlattSolver::eq_right(double x, double y){
    return 2*log10(x*sqrt(y))-0.8;
}
