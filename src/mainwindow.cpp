#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plotter.h"
#include "dateneingabe.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    DatenEingabe dateneingabe;
    dateneingabe.setModal(true);
    dateneingabe.exec();

}
