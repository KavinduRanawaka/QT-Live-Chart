/********************************************************************************
** Form generated from reading UI file 'portdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PORTDIALOG_H
#define UI_PORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PortDialog
{
public:

    void setupUi(QWidget *PortDialog)
    {
        if (PortDialog->objectName().isEmpty())
            PortDialog->setObjectName("PortDialog");
        PortDialog->resize(400, 300);

        retranslateUi(PortDialog);

        QMetaObject::connectSlotsByName(PortDialog);
    } // setupUi

    void retranslateUi(QWidget *PortDialog)
    {
        PortDialog->setWindowTitle(QCoreApplication::translate("PortDialog", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PortDialog: public Ui_PortDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PORTDIALOG_H
