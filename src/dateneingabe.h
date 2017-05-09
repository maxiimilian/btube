#ifndef DATENEINGABE_H
#define DATENEINGABE_H

#include <QDialog>

namespace Ui {
class DatenEingabe;
}

class DatenEingabe : public QDialog
{
    Q_OBJECT

public:
    explicit DatenEingabe(QWidget *parent = 0);
    ~DatenEingabe();

private:
    Ui::DatenEingabe *ui;
};

#endif // DATENEINGABE_H
