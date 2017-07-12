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

    // Funktionen für den Button und die Check-Boxen werden gesetzt
    void on_pushButton_clicked();

    void on_Wasser_clicked();

    void on_Oel_clicked();

    void on_Luft_clicked();

    void on_Benutzerdefiniert_clicked();

private:

    Ui::DatenEingabe *ui;

};

#endif // DATENEINGABE_H
