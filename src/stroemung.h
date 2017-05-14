#include "rohr.h"
#include "fluid.h"

#ifndef STROEMUNG_H
#define STROEMUNG_H

class Rohrstroemung
{
    private:
        Rohr rohr;
        Fluid fluid;
    public:
        // Konstruktor
        Rohrstroemung(Rohr rohr, Fluid fluid);

        // Reynoldszahl berechnen
        double get_Re();

        // Rohrreibungszahl Lambda berechnen
        double get_lambda();
};


#endif // STROEMUNG_H
