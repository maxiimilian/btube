#include "dateneingabe.h"
#include "ui_dateneingabe.h"
#include "rohr.h"
#include "fluid.h"
#include "plotter.h"
#include "stroemung.h"


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

void DatenEingabe::on_Benutzerdefiniert_clicked()

{

}

void DatenEingabe::on_pushButton_clicked()
{

        double laenge=ui->laenge->value();
        double radius=ui->radius->value();
        Rohr rohr(laenge, radius);

        double p_ein=ui->druckein->value();

        rohr.set_alpha_innen(300);
        rohr.set_alpha_aussen(400);
        rohr.set_t_aussen(0);

        double dichte_in=ui->Dichte->value(); // Benutzer legt Werte für Parameter fest // Überprüfung der Werte muss noch erfolgen
        double nue_in=ui->Viskositaet->value();
        double massenstrom_in=ui->Massenstrom->value();
        double cp_in=ui->cpwert->value();
        double t_ein = 20;

        Fluid fluid(dichte_in, nue_in, cp_in);
        fluid.set_massenstrom(massenstrom_in);
        fluid.set_t_ein(t_ein);

        Plotter plotter;        //Modal-Approach
        plotter.erstellePlot(rohr, fluid);

    plotter.setModal(true);
    plotter.exec();
}
