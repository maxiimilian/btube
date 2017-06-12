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
    Rohrstroemung rohrstroemung(&rohr, &fluid);

    /// Temperaturprofil
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
    ui->tempGraph->xAxis->setRange(0, l);

    if (rohr.get_t_aussen() >= fluid.get_t_ein()){

        double axis_plus = (rohr.get_t_aussen()-fluid.get_t_ein())/10;

        ui->tempGraph->yAxis->setRange(fluid.get_t_ein() - axis_plus, rohr.get_t_aussen() + axis_plus);
    }

    else{
        double axis_plus = (fluid.get_t_ein()-rohr.get_t_aussen())/10;
        ui->tempGraph->yAxis->setRange(rohr.get_t_aussen() -axis_plus, fluid.get_t_ein()+axis_plus);
    }
    ui->tempGraph->replot();



    /// Druckgradient
    QVector<double> g(101), m(101);
    {
    }

    ui->druckGraph->addGraph();
    ui->druckGraph->graph(0)->setData(g, m);


    ui->druckGraph->replot();




    /// Strömungsprofil
    /// Möglichkeit die Farbskala durch Dragging oder Zoomen zu ändern
    ui->speedGraph->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    ui->speedGraph->axisRect()->setupFullAxesBox(true);

    /// Achsenbeschriftung
    ui->speedGraph->xAxis->setLabel("Länge in [m]");
    ui->speedGraph->yAxis->setLabel("Radius in [m]");

    /*!
     * \brief aufstellen der QCPColorMap
     * \warning  Wir verwenden die Variablen s (normalerweise x) t (normalerweise y) und u (normalerweise z) damit dies nicht mit den Vatriablen aus
        dem Temperaturprofil kollidiert
     */
    QCPColorMap *colorMap = new QCPColorMap(ui->speedGraph->xAxis, ui->speedGraph->yAxis);
    int ns = 200;
    int nt = 200;

    /*! \brief Größe der ColorMap wird festgelegt
     *
     * Die ColorMap wird ns*nt groß sein bzw. Bildpunkte haben.
     * Der Achsberecheich für die x-Achse geht von 0 über die gesamte Länge des Rohres. Der Achsbereich für die y-Achse geht über den Gesamtenquerschnitt (von -r bis r)
     */
    colorMap->data()->setSize(ns, nt);
    colorMap->data()->setRange(QCPRange(0, rohr.get_laenge()), QCPRange((-1)*rohr.get_radius(), rohr.get_radius()));

    /*!
     * \brief Iterartion über die Strömungsfunktion und Speicherung der Werte in einer Cell.
     * \warning  Wir verwenden die Variablen s (normalerweise x) t (normalerweise y) und u (normalerweise z) damit dies nicht mit den Vatriablen aus
        dem Temperaturprofil kollidiert
     *
     * Über die multivariate Funktion der Geschwindigkeit wird mittels zweier for-Schleifen iteriert. Die Daten werden dann der QColorMap zugewiesen
     */
    double s;
    double t;
    double u;
    for (int sIndex=0; sIndex<ns; ++sIndex)
    {
      for (int tIndex=0; tIndex<ns; ++tIndex)
      {
          // Testfunktion und wird noch ersetzt
        colorMap->data()->cellToCoord(sIndex, tIndex, &s, &t);
        double r = 3*qSqrt(s*s+t*t)+1e-2;
        u = 2*s*(qCos(r+2)/r-qSin(r+2)/r)+1;
        colorMap->data()->setCell(sIndex, tIndex, u);
      }
    }

    /// Hinzufügen der Farbskala
    QCPColorScale *colorScale = new QCPColorScale(ui->speedGraph);

    /// Skala wird der richtigen Achse zugewiesen
    ui->speedGraph->plotLayout()->addElement(0, 1, colorScale);

    /// Vertikale Farbskala auf der rechten Seite
    colorScale->setType(QCPAxis::atRight);

    /// Verbindung von Farbe der Skala mit der Farbe der ColorMap
    colorMap->setColorScale(colorScale);

    /// Hinzufügen der Skalenbeschriftung
    colorScale->axis()->setLabel("Geschwindigkeit in [m/s]");

    /*!
     * \brief Laden eines Farbgradient aus den Voreinstellung
     *
     * gpJet ist ein Fabrverlauf der für numerische Analysen verwendet wird und passt daher auf unseren Anwendungsfall
     */
    colorMap->setGradient(QCPColorGradient::gpJet);
    /*!
     * \brief Die Farbdimension wird so angepasst, sodass alle erzeugten Datenpunkten auch eine Farbe zugewiesen bekommen.
     *
     * Die Anpassung an die Werte geschieht automatisch, sodass die Bandbreite von der geringsten auftretenden Greschwindigkeit zur maximalen Geschwindigkeit geht.
     */
    colorMap->rescaleDataRange();

    /// Achsen und ColorMap an sich sollen direkt aneinaderliegen:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->speedGraph);
    ui->speedGraph->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    /// Anpassung der Größe der Achsen an Widgetgröße:
    ui->speedGraph->rescaleAxes();


}
