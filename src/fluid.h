#ifndef FLUID_H
#define FLUID_H

/*!
 * \brief Stellt ein Fluid zur Verfügung
 */
class Fluid 
{
    private:
        /// Dichte des Fluids [kg/m^3]
        double dichte;

        /// kinematische Viskosität [m^2/s]
        double nue;

        /// Massenstrom [kg/s]
        double massenstrom;

        /// spez. isobare Wärmekapazität [J/(kg*K)]
        double cp;

        /// Eintrittstemperatur [K]
        double t_ein;

    public:
        /***************
        * Konstruktor *
        ***************/
        Fluid(double dichte, double nue, double cp);      // Maximilian Pyrzina & Simon Thel

        /***************
         * GET methods *
         ***************/
        /// Massenstrom wird zurückgegeben
        double get_massenstrom();                         // Simon Thel

        /// Dichte wird zurückgegeben
        double get_dichte();                              // Simon Thel

        /// kinematische Viskosität wird zurückgegen
        double get_nue();                                 // Simon Thel

        /// Wärmekapazität wird zurückgegeben
        double get_cp();                                  // Simon Thel

        /// Wärmekapazitätsstrom wird zurückgegen
        double get_cp_strom();                            // Simon Thel

        /// Gibt Eintrittstemperatur des Fluids zurück
        double get_t_ein();                               // Simon Thel

        /// dynamische Viskosität wird zurückgegeben
        double get_my();

        /// Gibt Massenstrom zurück (für Testing)
        double get_massenstrom_test();

        /***************
         * SET methods *
         ***************/
        /// Setzt den Massenstrom des Fluids
        void set_massenstrom(double massenstrom);

        /// Setzt die Eintrittstemperatur
        void set_t_ein (double t_ein);                   // Simon Thel
};
#endif 
