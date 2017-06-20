#ifndef PLOTTER_H
#define PLOTTER_H
#include "fluid.h"
#include "rohr.h"
#include <QDialog>

namespace Ui {
class Plotter;
}

/// Erstellung einer neuen Klasse mit dem Namen Plotter
class Plotter : public QDialog
{
    Q_OBJECT

public:

    /// Konstruktorinitialiserung; "explict" verhindert versehentliche Übergabe von anderen Datentypen und deren Konvertierung in ein QWidget.
    explicit Plotter(QWidget *parent = 0);
    /// Destruktorinitialisierung
    ~Plotter();
    /// Plotterfunktion mit der Übergabe der Datentypen Rohr und Fluid
    void erstellePlot(Rohr rohr, Fluid fluid);

private:
    Ui::Plotter *ui;
};

#endif // PLOTTER_H
