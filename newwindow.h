#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class NewWindow;
}

class NewWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewWindow(QWidget *parent = nullptr, double* yData = nullptr);
    ~NewWindow();

private:
    Ui::NewWindow *ui;
    double* yData;
};

#endif // NEWWINDOW_H
