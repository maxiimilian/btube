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

    /*
    void set_argv (char **argv);

    char** get_argv();
    */

private slots:

    void on_pushButton_clicked();

private:

    // char* argv;

    Ui::DatenEingabe *ui;

};

#endif // DATENEINGABE_H
