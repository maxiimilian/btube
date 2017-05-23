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

    public:
        Fluid();
        Fluid(double dichte, double massenstrom, double nue);

        /// Massenstrom wird zurückgegeben
        double get_massenstrom();
        /// Dichte wird zurückgegeben
        double get_dichte();
        /// Viskosität wird zurückgegeb
        double get_nue();      
};

#endif 
