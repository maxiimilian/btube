#include "QMessageBox"
#include <string>

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

// Werte für Wasser werden festgelegt und in der jeweiligen SpinBox angezeigt
void DatenEingabe::on_Wasser_clicked()
{
    ui->Dichte->setValue(1000);
    ui->Viskositaet->setValue(.00001);
    ui->cpwert->setValue(4182);
}

// Werte für Öl, hier Olivenöl, werden festgelegt und in der jeweiligen SpinBox angezeigt
void DatenEingabe::on_Oel_clicked()
{
    ui->Dichte->setValue(910);
    ui->Viskositaet->setValue(0.000084);
    ui->cpwert->setValue(1970);
}

// Werte für Luft werden festgelegt und in der jeweiligen SpinBox angezeigt
void DatenEingabe::on_Luft_clicked()
{
    ui->Dichte->setValue(1.293);
    ui->Viskositaet->setValue(.000017);
    ui->cpwert->setValue(1005);
}

// Werte für Benutzerdefiniert werden in den SpinBoxen auf Null gesetzt
void DatenEingabe::on_Benutzerdefiniert_clicked()
{
    ui->Dichte->setValue(0);
    ui->Viskositaet->setValue(0);
    ui->cpwert->setValue(0);
}

void DatenEingabe::on_pushButton_clicked()
{
        // Werte für die Erstellung des Rohrs werden aus der GUI eingelesen und gespeichert
        double laenge=ui->laenge->value();
        double radius=ui->radius->value();
        double k_s=ui->ksrohr->value()/1e6;

        // Druck, Konvektionswiderstände, Temperaturen, Massenstrom, Dichte, Viskosität und cp-Wert werden aus der GUI eingelesen und gespeichert
        double p_ein=ui->druckein->value();
        double alpha_innen=ui->alpha_innen->value();
        double alpha_aussen=ui->alpha_aussen->value();
        double t_aus=ui->temp_aussen->value();
        double massenstrom_in=ui->Massenstrom->value();
        double t_ein=ui->temp_Innen->value();
        double dichte_in=ui->Dichte->value();
        double nue_in=ui->Viskositaet->value();
        double cp_in=ui->cpwert->value();

        // Leeren Rohrpointer erstellen
        Rohr* rohr_ptr = NULL;
        try{
            // Rohrobjekt auf Rohrpointer erstellen und eventuelle Exceptions abfangen
            rohr_ptr = new Rohr(laenge, radius, k_s);

            // Parameter für das Rohr werden festgesetzt
            rohr_ptr->set_alpha_innen(alpha_innen);
            rohr_ptr->set_alpha_aussen(alpha_aussen);
            rohr_ptr->set_t_aussen(t_aus);
            rohr_ptr->set_startpressure(p_ein);
        }
        catch (const std::exception& e) {
            // Fehlermeldung ausgeben...
            this->show_warning(e.what());
            // ... und Initialisierung nicht weiter fortführen
            return;
        }

        // Leeren Fluidpointer erstellen
        Fluid* fluid_ptr = NULL;

        // Erstellung des Fluides
        try {
            fluid_ptr = new Fluid(dichte_in, nue_in, cp_in);
            fluid_ptr->set_massenstrom(massenstrom_in);
            fluid_ptr->set_t_ein(t_ein);
        } catch (const std::exception& e) {
            // Fehlermeldung ausgeben...
            this->show_warning(e.what());
            // ... und Initialisierung nicht weiter fortführen
            return;
        }


        Rohrstroemung rohrstroemung(rohr_ptr, fluid_ptr);
        rohrstroemung.set_druckverlauf();
        rohrstroemung.print_druckverlauf();


        try {
            // Öffnet einen Dialog/Fenster, dass die Bearbeitung des Elternfenster verhindert
            Plotter plotter;
            plotter.erstellePlot(rohr_ptr, fluid_ptr);
            plotter.setModal(true);
            plotter.exec();
        } catch (const std::exception& e) {
            // Fehlermeldung ausgeben...
            this->show_warning(e.what());
            // ... und Initialisierung nicht weiter fortführen
            return;
        }
}

void DatenEingabe::show_warning(const char* msg){
    // Messagebox initialisieren
    QMessageBox errorbox;
    errorbox.setIcon(QMessageBox::Warning);
    // Fenstertitel setzen
    errorbox.setWindowTitle("Warnung - Ungültige Eingabe");
    // Nachricht setzen
    errorbox.setText(msg);
    errorbox.exec();
}
