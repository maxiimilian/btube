#ifndef DATENEINGABE_H
#define DATENEINGABE_H

#include <QDialog>
#include <QDoubleSpinBox>
#include <QRadioButton>

namespace Ui {
class DatenEingabe;
}

class DatenEingabe : public QDialog
{
    Q_OBJECT

public:
    explicit DatenEingabe(QWidget *parent = 0);
    ~DatenEingabe();

private slots:

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_pushButton_clicked();

    Ui::DatenEingabe *ui;

};

#endif // DATENEINGABE_H
