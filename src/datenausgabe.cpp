#include "datenausgabe.h"
#include "ui_datenausgabe.h"

DatenAusgabe::DatenAusgabe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatenAusgabe)
{
    ui->setupUi(this);
}

DatenAusgabe::~DatenAusgabe()
{
    delete ui;
}
