#ifndef DATAGRAPHWIDGET_H
#define DATAGRAPHWIDGET_H

#include <QWidget>

namespace Ui {
class DataGraphWidget;
}

class DataGraphWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataGraphWidget(QWidget *parent = nullptr);
    ~DataGraphWidget();

private:
    Ui::DataGraphWidget *ui;
};

#endif // DATAGRAPHWIDGET_H
