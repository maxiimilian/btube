#ifndef PLOTTER_H
#define PLOTTER_H
#include "fluid.h"
#include "rohr.h"
#include <QDialog>

namespace Ui {
class Plotter;
}

class Plotter : public QDialog
{
    Q_OBJECT

public:

    explicit Plotter(QWidget *parent = 0);
    ~Plotter();
    void erstellePlot(Rohr rohr, Fluid fluid);

private:
    Ui::Plotter *ui;
};

#endif // PLOTTER_H
