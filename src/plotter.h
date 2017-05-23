#ifndef PLOTTER_H
#define PLOTTER_H

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

private slots:
    void erstellePlot();
private:
    Ui::Plotter *ui;
};

#endif // PLOTTER_H
