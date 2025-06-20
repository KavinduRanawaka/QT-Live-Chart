#include "portdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSerialPortInfo>
#include <QLabel>

PortDialog::PortDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Select Serial Port");

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Available Ports:");
    layout->addWidget(label);

    portComboBox = new QComboBox(this);
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        portComboBox->addItem(info.portName());
    }
    layout->addWidget(portComboBox);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    QPushButton *okBtn = new QPushButton("Open");
    QPushButton *cancelBtn = new QPushButton("Cancel");
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
    layout->addLayout(btnLayout);

    connect(okBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

QString PortDialog::selectedPort() const {
    return portComboBox->currentText();
}
