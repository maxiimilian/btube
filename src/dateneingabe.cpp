#include "dateneingabe.h"
#include "ui_dateneingabe.h"

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
