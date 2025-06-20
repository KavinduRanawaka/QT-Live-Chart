#ifndef PORTDIALOG_H
#define PORTDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>

class PortDialog : public QDialog {
    Q_OBJECT
public:
    explicit PortDialog(QWidget *parent = nullptr);
    QString selectedPort() const;

private:
    QComboBox *portComboBox;
};

#endif // PORTDIALOG_H
