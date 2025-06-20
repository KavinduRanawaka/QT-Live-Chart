#include "datagraphwidget.h"
#include "ui_datagraphwidget.h"

DataGraphWidget::DataGraphWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataGraphWidget)
{
    ui->setupUi(this);
}

DataGraphWidget::~DataGraphWidget()
{
    delete ui;
}
