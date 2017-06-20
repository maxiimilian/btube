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


void DatenEingabe::on_pushButton_clicked()
{

        double laenge=ui->laenge->value();
        double radius=ui->radius->value();
        double k_s = 5e-6;
        double p_ein=ui->druckein->value();

        Rohr rohr(laenge, radius, k_s);


        rohr.set_startpressure(p_ein);
        rohr.set_alpha_innen(300);
        rohr.set_alpha_aussen(400);
        rohr.set_t_aussen(0);

        double dichte_in=ui->Dichte->value(); // Benutzer legt Werte für Parameter fest // Überprüfung der Werte muss noch erfolgen
        double nue_in=ui->Viskositaet->value();
        double massenstrom_in=ui->Massenstrom->value();
        double cp_in=ui->cpwert->value();
        double t_ein = 20;    

        Rohrstroemung rohrstroemung(&rohr, &fluid);
        rohrstroemung.set_druckverlauf();
        rohrstroemung.print_druckverlauf();
        rohr.set_alpha_innen(alpha_innen);
        rohr.set_alpha_aussen(alpha_aussen);
        rohr.set_t_aussen(t_aus);


        if(ui->Wasser->isChecked()){
            dichte_in = 1000;
            nue_in = 10e-6;
            cp_in = 4182;
        }

        if(ui->Luft->isChecked()){
            dichte_in = 1.293;
            nue_in = 1558;
            cp_in = 1005;
        }

        if(ui->Oel->isChecked()){
            dichte_in = 910;
            nue_in = 107.5;
            cp_in = 1970;
        }

        if(ui->Benutzerdefiniert->isChecked()){
            dichte_in=ui->Dichte->value(); // Benutzer legt Werte für Parameter fest // Überprüfung der Werte muss noch erfolgen
            nue_in=ui->Viskositaet->value();
            cp_in=ui->cpwert->value();
        }

        Fluid fluid(dichte_in, nue_in, cp_in);
        fluid.set_massenstrom(massenstrom_in);
        fluid.set_t_ein(t_ein);

        Plotter plotter;        //Modal-Approach
        plotter.erstellePlot(rohr, fluid);

    plotter.setModal(true);
    plotter.exec();
}
