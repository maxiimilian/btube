#include "plotter.h"
#include "ui_plotter.h"
#include "rohr.h"
#include "fluid.h"
#include "stroemung.h"


Plotter::Plotter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Plotter)
{
    ui->setupUi(this);
}
Plotter::~Plotter()
{
    delete ui;
}

void Plotter::erstellePlot(Rohr rohr, Fluid fluid)
{
    Rohrstroemung rohrstroemung(rohr, fluid);

    ///Anlegen der Länge als Variable damit Koordinatensystem und for-Schleife angepasst werde
    double l = rohr.get_laenge();
    /// initilaisieren von QVectoren mit Einträgen von 0..100
    QVector<double> x(101), y(101);

    ///Iterieren über ortsabhängige get_temp-Funktion
    for (int i=0; i<=100; ++i)  //Es müssen 100 Einträgegefüllt werden
    {
      x[i] = i * (l/100);
      y[i] = rohrstroemung.get_temp(i * (l/100));

    }
    /// Graphen erstellen und Achsen festlegen:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    /// Achsenbeschriftung:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    /// Achsenbereich
    ///x-Achse geht von 0 bis zur Länge des Rohres
    ui->customPlot->xAxis->setRange(0, l);

    ///Unterscheidung ob t_aussen oder t_ein größer ist; entsprechendes Setzen der y-Achsenbereichs
    if (rohr.get_t_aussen() >= fluid.get_t_ein()){

        ///Bestimmung eines Wertes damit die größten/kleinsten Werte nicht am Rand liegen
        double axis_plus = (rohr.get_t_aussen()-fluid.get_t_ein())/10;

        ///y-Achse beginnt kurz unter t_ein und endet kurz über t_aussen
        ui->customPlot->yAxis->setRange(fluid.get_t_ein() - axis_plus, rohr.get_t_aussen() + axis_plus);
    }

    ///Analoges Vorgehen wie im if-Statement \sa if(rohr.get_t_aussen >= fluid.get_t_ein())
    else{
        double axis_plus = (fluid.get_t_ein()-rohr.get_t_aussen())/10;
        ui->customPlot->yAxis->setRange(rohr.get_t_aussen() -axis_plus, fluid.get_t_ein()+axis_plus);
    }
    ui->customPlot->replot();

}
