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
//Folgende Zeilen dienen nur zu Testzwecken der Plotter-Funktion für den Temperatur verlauf und sind eigentlich Teil der Eingabe-Funktion
    Rohr rohr(37, 0.5);

    rohr.set_alpha_innen(300);
    rohr.set_alpha_aussen(400);
    rohr.set_t_aussen(0);

    double massenstrom_in = 10;
    double dichte_in = 1000;
    double nue_in = 5e-6;
    double cp_in = 4182;
    double t_ein = 20;

    Fluid fluid(dichte_in, nue_in, cp_in);
    fluid.set_massenstrom(massenstrom_in);
    fluid.set_t_ein(t_ein);
//Ende der Test-Eingabe

    Plotter::erstellePlot(rohr, fluid);
}

Plotter::~Plotter()
{
    delete ui;
}

void Plotter::erstellePlot(Rohr rohr, Fluid fluid)
{
    Rohrstroemung rohrstroemung(rohr, fluid);
    ///Temperaturprofil
    ///Anlegen der Länge als Variable damit Koordinatensystem und for-Schleife angepasst werde
    double l = rohr.get_laenge();
    /// initilaisieren von QVectoren mit Einträgen von 0..100
    QVector<double> x(101), y(101);

    ///Iterieren über ortsabhängige get_temp-Funktion
    for (int i=0; i<=100; ++i)  //Es müssen 100 Einträge gefüllt werden
    {
      x[i] = i * (l/100);
      y[i] = rohrstroemung.get_temp(i * (l/100));

    }
    /// Graphen erstellen und Achsen festlegen:
    ui->tempGraph->addGraph();
    ui->tempGraph->graph(0)->setData(x, y);
    /// Achsenbeschriftung:
    ui->tempGraph->xAxis->setLabel("Länge in [m]");
    ui->tempGraph->yAxis->setLabel("Temperatur des Fluids in [K]");

    /// Achsenbereich
    ///x-Achse geht von 0 bis zur Länge des Rohres
    ui->tempGraph->xAxis->setRange(0, l);

    ///Unterscheidung ob t_aussen oder t_ein größer ist; entsprechendes Setzen der y-Achsenbereichs
    if (rohr.get_t_aussen() >= fluid.get_t_ein()){

        ///Bestimmung eines Wertes damit die größten/kleinsten Werte nicht am Rand liegen
        double axis_plus = (rohr.get_t_aussen()-fluid.get_t_ein())/10;

        ///y-Achse beginnt kurz unter t_ein und endet kurz über t_aussen
        ui->tempGraph->yAxis->setRange(fluid.get_t_ein() - axis_plus, rohr.get_t_aussen() + axis_plus);
    }

    ///Analoges Vorgehen wie im if-Statement \sa if(rohr.get_t_aussen >= fluid.get_t_ein())
    else{
        double axis_plus = (fluid.get_t_ein()-rohr.get_t_aussen())/10;
        ui->tempGraph->yAxis->setRange(rohr.get_t_aussen() -axis_plus, fluid.get_t_ein()+axis_plus);
    }
    ui->tempGraph->replot();




    /// Druckgradient
    QVector<double> g(101), m(101);
    for (int i=0; i<101; ++i)
    {
      g[i] = i/50.0 - 1;
      m[i] = 0.6-g[i];
    }

    ui->druckGraph->addGraph();
    ui->druckGraph->graph(0)->setData(g, m);

    ui->druckGraph->xAxis->setLabel("x");
    ui->druckGraph->yAxis->setLabel("y");

    ui->druckGraph->xAxis->setRange(-1, 1);
    ui->druckGraph->yAxis->setRange(0, 1);
    ui->druckGraph->replot();




    /// Strömungsprofil
    ui->speedGraph->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // Möglichkeit die Farbskala durch Dragging oder Zoomen zu ändern
    ui->speedGraph->axisRect()->setupFullAxesBox(true);
    ui->speedGraph->xAxis->setLabel("x");
    ui->speedGraph->yAxis->setLabel("y");

    // aufstellen der QCPColorMap: Wir verwenden die Variablen s (normalerweise x) t (normalerweise y) und z (normalerweise z) damit dies nicht mit den Vatriablen aus
    // dem Temperaturprofil kollidiert
    QCPColorMap *colorMap = new QCPColorMap(ui->speedGraph->xAxis, ui->speedGraph->yAxis);
    int ns = 200;
    int nt = 200;
    colorMap->data()->setSize(ns, nt); // die ColorMap wird ns*nt groß sein
    colorMap->data()->setRange(QCPRange(-4, 4), QCPRange(-4, 4)); // Achsenbandbreit (-4..4) wird s und t zugewiesen
    // Machen wir mal eine coole multivairate Funktion
    double s, t, u;
    for (int sIndex=0; sIndex<ns; ++sIndex)
    {
      for (int tIndex=0; tIndex<ns; ++tIndex)
      {
        colorMap->data()->cellToCoord(sIndex, tIndex, &s, &t);
        double r = 3*qSqrt(s*s+t*t)+1e-2;
        u = 2*s*(qCos(r+2)/r-qSin(r+2)/r);
        colorMap->data()->setCell(sIndex, tIndex, u);
      }
    }

    // Hinzufügen der Farbskala
    QCPColorScale *colorScale = new QCPColorScale(ui->speedGraph);
    ui->speedGraph->plotLayout()->addElement(0, 1, colorScale); // Skala wird der richtigen Achse zugewiesen
    colorScale->setType(QCPAxis::atRight); // Vertikale Farbskala auf der rechten Seite
    colorMap->setColorScale(colorScale); // Verbindung von Farbe der Skala mit der Farbe der ColorMap
    colorScale->axis()->setLabel("Irgendwas Cooles");

    // Es wird hier ein Farbgradient aus den Voreinstellungen geladen:
    colorMap->setGradient(QCPColorGradient::gpPolar);

    // Die Farbdimension wird so angepasst, sodass alle erzeugten Datenpunkten auch eine Farbe zugewiesen bekommen
    colorMap->rescaleDataRange();

    // Achsen und ColorMap an sich sollen direkt aneinaderliegen:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->speedGraph);
    ui->speedGraph->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // Anpassung der Größe der Achsen an Widgetgröße:
    ui->speedGraph->rescaleAxes();


}
