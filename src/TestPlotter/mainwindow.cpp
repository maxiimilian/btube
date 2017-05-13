#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::makePlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makePlot()
{
    //Daten erstellen
    QVector<double> x(101), y(101); // initialisieren mit den Einträgen 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x geht von -1 bis 1
      y[i] = x[i]*x[i]; // Parabel
    }
    // Graph erstellen und Daten zuweisen
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // Achsenbeschriftung
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // Achsenbereich
    ui->customPlot->xAxis->setRange(-1, 1);
    ui->customPlot->yAxis->setRange(0, 1);
    ui->customPlot->replot();

}
