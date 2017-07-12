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
        /// \author Maximilian Pierzyna & Simon Thel
        Fluid(double dichte, double nue, double cp);

        /***************
         * GET methods *
         ***************/
        /// Massenstrom wird zurückgegeben
        /// \author Simon Thel
        double get_massenstrom();

        /// Dichte wird zurückgegeben
        /// \author Simon Thel
        double get_dichte();

        /// kinematische Viskosität wird zurückgegen
        /// \author Simon Thel
        double get_nue();

        /// Wärmekapazität wird zurückgegeben
        /// \author Simon Thel
        double get_cp();

        /// Wärmekapazitätsstrom wird zurückgegen
        /// \author Simon Thel
        double get_cp_strom();

        /// Gibt Eintrittstemperatur des Fluids zurück
        /// \author Simon Thel
        double get_t_ein();

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
        /// \author Simon Thel
        void set_t_ein (double t_ein);
};
#endif 
