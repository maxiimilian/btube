#include "dateneingabe.h"
#include "ui_dateneingabe.h"
#include "rohr.h"
#include "fluid.h"
#include "mainwindow.h"
#include "plotter.h"


DatenEingabe::DatenEingabe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatenEingabe)
{
    ui->setupUi(this);

}

DatenEingabe::~DatenEingabe()
{
    delete ui;
}

// Einlesen der Daten aus den DoubleSpin Boxen Objekten

void DatenEingabe::on_doubleSpinBox_valueChanged(double arg1)
{
    double laenge = arg1;
}



void DatenEingabe::on_doubleSpinBox_2_valueChanged(double arg2)
{
    double radius = arg2;
}

// Festlegen der Werte für das Fluid mit Hilfe der Radio Boxen

void DatenEingabe::on_radioButton_clicked()
{
    double dichte = 0;
}

void DatenEingabe::on_pushButton_clicked()
{
    Plotter plotter;        //Modal-Approach
    plotter.setModal(true);
    plotter.exec();
}
