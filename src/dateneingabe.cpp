#include "dateneingabe.h"
#include "ui_dateneingabe.h"
#include "rohr.h"
#include "fluid.h"
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

void DatenEingabe::on_Wasser_clicked() //Stoffwerte für Wasser
{
     double dichte;
}

void DatenEingabe::on_Oel_clicked() //Stoffwerte für Öl
{
     double dichte;
}

void DatenEingabe::on_Luft_clicked() //Stoffwerte für Luft
{
     double dichte;
}

void DatenEingabe::on_Benutzerdefiniert_clicked() //Stoffwerte für benutzerdefiniertes Fluid
{
        double dichte=ui->Dichte->value(); // Benutzer legt Werte für Parameter fest // Überprüfung der Werte muss noch erfolgen
        double nue=ui->Viskositaet->value();
        double massenstrom=ui->Massenstrom->value();
        double cp=ui->cpwert->value();
}

void DatenEingabe::on_pushButton_clicked()
{
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

        Plotter plotter;        //Modal-Approach
        plotter.erstellePlot(rohr, fluid);

    plotter.setModal(true);
    plotter.exec();
}

