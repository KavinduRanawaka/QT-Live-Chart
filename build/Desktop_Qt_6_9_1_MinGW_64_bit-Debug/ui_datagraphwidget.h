/********************************************************************************
** Form generated from reading UI file 'datagraphwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAGRAPHWIDGET_H
#define UI_DATAGRAPHWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataGraphWidget
{
public:

    void setupUi(QWidget *DataGraphWidget)
    {
        if (DataGraphWidget->objectName().isEmpty())
            DataGraphWidget->setObjectName("DataGraphWidget");
        DataGraphWidget->resize(400, 300);

        retranslateUi(DataGraphWidget);

        QMetaObject::connectSlotsByName(DataGraphWidget);
    } // setupUi

    void retranslateUi(QWidget *DataGraphWidget)
    {
        DataGraphWidget->setWindowTitle(QCoreApplication::translate("DataGraphWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataGraphWidget: public Ui_DataGraphWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAGRAPHWIDGET_H
