#ifndef DATENEINGABE_H
#define DATENEINGABE_H

#include <QDialog>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <string>

namespace Ui {
class DatenEingabe;
}

class DatenEingabe : public QDialog
{
    Q_OBJECT

public:
    explicit DatenEingabe(QWidget *parent = 0);
    ~DatenEingabe();

    /// Show a QMessageBox Warning with the given message
    void show_warning(const char *msg);

private slots:

    void on_pushButton_clicked();

private:

    Ui::DatenEingabe *ui;

};

#endif // DATENEINGABE_H
