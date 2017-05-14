#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plotter.h"

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




void MainWindow::on_pushButton_clicked()
{
    Plotter plotter;        //Modal-Approach
    plotter.setModal(true);
    plotter.exec();
}
