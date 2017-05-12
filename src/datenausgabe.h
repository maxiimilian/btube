#ifndef DATENAUSGABE_H
#define DATENAUSGABE_H

#include <QWidget>

namespace Ui {
class DatenAusgabe;
}

class DatenAusgabe : public QWidget
{
    Q_OBJECT

public:
    explicit DatenAusgabe(QWidget *parent = 0);
    ~DatenAusgabe();

private slots:
    void erstellePlot();

private:
    Ui::DatenAusgabe *ui;
};

#endif // DATENAUSGABE_H
