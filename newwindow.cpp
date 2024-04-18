#include "newwindow.h"
#include "ui_newwindow.h"

NewWindow::NewWindow(QWidget *parent, double* yData) :
    QWidget(parent),
    ui(new Ui::NewWindow),
    yData(yData)
{
    ui->setupUi(this);

    ui->myPlot->addGraph();
    ui->myPlot->xAxis->setLabel("X");
    ui->myPlot->xAxis->setRange(0, 30);
    ui->myPlot->yAxis->setLabel("Y");
    ui->myPlot->yAxis->setRange(-15, 15);

    for(int i = 0; i < 3000; i++) {
        ui->myPlot->graph(0)->addData(i / 100.0f, yData[i]);
    }

    ui->myPlot->replot();
}

NewWindow::~NewWindow()
{
    delete ui;
}
