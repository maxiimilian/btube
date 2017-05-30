#ifndef FLUID_H
#define FLUID_H

/*!
 * \brief Stellt ein Fluid zur Verfügung
 */
class Fluid 
{
    private:
        /// Dichte des Fluids
        double dichte;
        /// kinematische Viskosität
        double nue;
        /// Massenstrom
        double massenstrom;
        /// Wärmekapazität
        double cp;
        /// Wärmekapazitätsstrom
        double cp_strom;
        /// Eintrittstemperatur in Celcius oder Kelvin
        double t_ein;
        /// Umgebungstemperatur in Celcius oder Kelvin
        double t_aussen;

    public:
        Fluid();
        Fluid(double dichte, double nue, double cp);

        /// Massenstrom wird zurückgegeben
        double get_massenstrom();

        /// Dichte wird zurückgegeben
        double get_dichte();

        /// Viskosität wird zurückgegen
        double get_nue();

        /// Wärmekapazität wird zurückgegeben
        double get_cp();

        /// Wärmekapazitätsstrom wird zurückgegen
        double get_cp_strom();

        /// Gibt Eintrittstemperatur des Fluids zurück
        double get_t_ein();

        /// Gibt Außentemperatur zurück
        double get_t_aussen();

        /// Setzt den Massenstrom des Fluids
        void set_massenstrom(double massenstrom);


};

#endif 
