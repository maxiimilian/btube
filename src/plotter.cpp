#include "plotter.h"
#include "ui_plotter.h"

Plotter::Plotter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Plotter)
{
    ui->setupUi(this);
    Plotter::erstellePlot();
}

Plotter::~Plotter()
{
    delete ui;
}

void Plotter::erstellePlot()
{
    // Erstellen von Daten, die angezeigt werden sollen
    QVector<double> x(101), y(101); // initilaisieren mit Einträgen von 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1;
      y[i] = x[i]*x[i]; // Quadratische Funktion
    }
    // Graphen erstellen und Achsen festlegen:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // Achsenbeschriftung:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // Achsenbereich
    ui->customPlot->xAxis->setRange(-1, 1);
    ui->customPlot->yAxis->setRange(0, 1);
    ui->customPlot->replot();

}
