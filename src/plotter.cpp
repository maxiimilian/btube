///Präprozessoranweisungen
#include "plotter.h"
#include "ui_plotter.h"
#include "rohr.h"
#include "fluid.h"
#include "stroemung.h"

/// Konstruktor für die Plotterfunktion
Plotter::Plotter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Plotter)
{
    ui->setupUi(this);
}

/// Freigeben des Speicherplatzes nach Beenden des Plotters durch einen Destruktor
Plotter::~Plotter()
{
    delete ui;
}

int Plotter::erstellePlot(Rohr rohr, Fluid fluid)
{
    Rohrstroemung rohrstroemung(&rohr, &fluid);
    /// Anlegen der Länge und des Radius als Variable damit Koordinatensysteme und for-Schleifen angepasst werden. Diese Variablen werden in allen drei Plotter verwendet
    double l = rohr.get_laenge();
    double r = rohr.get_radius();

    /// Variable zum Zählen der Datenpunkte
    int datenpunkte = 0;

    /********************
     * Temperaturprofil *
     *********************/
    /// initilaisieren von QVectoren mit Einträgen von 0..100
    QVector<double> laenge_inkrement (101), temperatur (101);

    ///Iterieren über ortsabhängige get_temp-Funktion
    for (int i=0; i<=100; ++i)  //Es müssen 100 Einträge gefüllt werden
    {
      laenge_inkrement [i] = i * (l/100);
      temperatur [i] = rohrstroemung.get_temp(i * (l/100));

      ///Zählen der Datenpunkte
      datenpunkte++;
    }
    /// Graphen erstellen und Achsen festlegen:
    ui->tempGraph->addGraph();
    ui->tempGraph->graph(0)->setData(laenge_inkrement, temperatur);
    /// Achsenbeschriftung:
    ui->tempGraph->xAxis->setLabel("Länge in [m]");
    ui->tempGraph->yAxis->setLabel("Temperatur des Fluids in [K]");

    /// Achsenbereich
    /// x-Achse geht von 0 bis zur Länge des Rohres
    ui->tempGraph->xAxis->setRange(0, l);

    /// Unterscheidung ob t_aussen oder t_ein größer ist; entsprechendes Setzen der y-Achsenbereichs
    if (rohr.get_t_aussen() >= fluid.get_t_ein()){

        /// Bestimmung eines Wertes damit die größten/kleinsten Werte nicht am Rand liegen
        double axis_plus = (rohr.get_t_aussen()-fluid.get_t_ein())/10;

        /// y-Achse beginnt kurz unter t_ein und endet kurz über t_aussen
        ui->tempGraph->yAxis->setRange(fluid.get_t_ein() - axis_plus, rohr.get_t_aussen() + axis_plus);
    }

    /// Analoges Vorgehen wie im if-Statement
    /// \sa if(rohr.get_t_aussen >= fluid.get_t_ein())
    else{
        double axis_plus = (fluid.get_t_ein()-rohr.get_t_aussen())/10;
        ui->tempGraph->yAxis->setRange(rohr.get_t_aussen() -axis_plus, fluid.get_t_ein()+axis_plus);
    }
    ui->tempGraph->replot();

    /****************
     * Durckverlauf *
     ****************/

    /// Initilaisieren von einem QVector mit Einträgen von 0..100
    QVector<double> druck (101);
    for (int i=0; i<=100; ++i)
    {
      druck[i] = rohrstroemung.get_pressure(i * (l/100));

      ///Zählen der Datenpunkte
      datenpunkte++;
    }

    ui->druckGraph->addGraph();
    ui->druckGraph->graph(0)->setData(laenge_inkrement, druck);

    ui->druckGraph->xAxis->setLabel("Länge in [m]");
    ui->druckGraph->yAxis->setLabel("Druck in [bar]");

    /// Achsenbereich
    /// Bestimmung eines Wertes damit die größten/kleinsten Werte nicht am Rand liegen
    double axis_plus = (rohr.get_startpressure()-druck[100])/10;
    /// x-Achse geht von 0 bis zur Länge des Rohres
    ui->druckGraph->xAxis->setRange(0, l);

    /*!
     * \brief Legt den y-Achsenbereich fest
     *
     * Der Druck im Rohr wird aufgrund der Reibung ständig abnehmen. Eine Fallunterscheidung wie bei der Temperatur ist daher nicht nötig.
     * Der Bereich wird festgelegt vom niedirgsten Druckwert (m[100]) und dem Anfangsdruck. Zusätzlich wird noch ein Offset genau wie bei dem Temperaturverlauf berücksichtigt
     */
    ui->druckGraph->yAxis->setRange(druck[100]-axis_plus, rohr.get_startpressure()+axis_plus);

    ui->druckGraph->replot();


    /*******************
     * Strömungsprofil *
     *******************/
    /// Möglichkeit die Farbskala durch Dragging oder Zoomen zu ändern
    ui->speedGraph->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    ui->speedGraph->axisRect()->setupFullAxesBox(true);

    /// Achsenbeschriftung
    ui->speedGraph->xAxis->setLabel("Länge in [m]");
    ui->speedGraph->yAxis->setLabel("Radius in [m]");

     ///aufstellen der QCPColorMap

    QCPColorMap *colorMap = new QCPColorMap(ui->speedGraph->xAxis, ui->speedGraph->yAxis);

    /*! \brief Größe der ColorMap wird festgelegt
     *
     * Die ColorMap wird anz_laenge_pkt*anz_radius_pkt groß sein bzw. Bildpunkte haben.
     * Der Achsberecheich für die x-Achse geht von 0 über die gesamte Länge des Rohres. Der Achsbereich für die y-Achse geht über den Gesamtenquerschnitt (von -r bis r)
     */
    int anz_laenge_pkt = 200;
    int anz_radius_pkt = 200;
    double laenge;
    double radius;
    double geschwindigkeit;
    colorMap->data()->setSize(anz_laenge_pkt, anz_radius_pkt);
    colorMap->data()->setRange(QCPRange(0, rohr.get_laenge()), QCPRange((-1)*rohr.get_radius(), rohr.get_radius()));

    /*!
     * \brief Iterartion über die Strömungsfunktion und Speicherung der Werte in einer Cell.
     *
     * Über die multivariate Funktion der Geschwindigkeit wird mittels zweier for-Schleifen iteriert. Die Daten werden dann der QColorMap zugewiesen
     */

    for (int laenge_index=0; laenge_index < anz_laenge_pkt; ++laenge_index)
    {
      for (int radius_index=0; radius_index < anz_radius_pkt; ++radius_index)
      {
       colorMap->data()->cellToCoord(laenge_index, radius_index, &laenge, &radius);

       /*!
        * \brief Anpassung der Iterationsschritte an die Länge und Radius des Rohrs.
        *
        * Der Radius geht von -r bis r, sodass dieser Iterationsschritt nur mit dem Faktor (r/100) angepasst werden muss
        */
       geschwindigkeit = rohrstroemung.get_stroemung(radius_index*(r/100), laenge_index*(l/200));
       colorMap->data()->setCell(laenge_index, radius_index, geschwindigkeit);

       ///Zählen der Datenpunkte
       datenpunkte++;
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

    ///Rückgabe des Testwerts
    return datenpunkte;
}
