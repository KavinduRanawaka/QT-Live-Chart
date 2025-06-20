// mainwindow.cpp
#include "mainwindow.h"
#include "portdialog.h"
#include <QMenuBar>
#include <QToolBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QDebug>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea(this);
    mdiArea->setStyleSheet("background-color: white;");

    taskBarWidget = new QWidget(this);
    taskBarLayout = new QHBoxLayout(taskBarWidget);
    taskBarLayout->setContentsMargins(5, 5, 5, 5);
    taskBarLayout->setSpacing(5);

    QWidget *central = new QWidget(this);
    QVBoxLayout *centralLayout = new QVBoxLayout(central);
    centralLayout->setContentsMargins(0, 0, 0, 0);
    centralLayout->setSpacing(0);
    centralLayout->addWidget(mdiArea);
    centralLayout->addWidget(taskBarWidget);
    setCentralWidget(central);

    serial = new QSerialPort(this);
    connect(serial, &QSerialPort::readyRead, this, [this]() {
        while (serial->canReadLine()) {
            QByteArray line = serial->readLine().trimmed();
            bool ok;
            int value = line.toInt(&ok);
            if (ok) {
                series->append(dataPointIndex++, value);
                // Keep last 100 points visible:
                if (dataPointIndex > 100) {
                    chart->scroll(chart->plotArea().width()/100, 0);
                    chart->axisX()->setRange(dataPointIndex - 100, dataPointIndex);
                }
            }
        }
    });


    setupMenuBar();
    setupToolBar();
    setupTaskBar();
    createPositionedSubWindows();
}

MainWindow::~MainWindow() {}

void MainWindow::setupMenuBar() {
    QMenu *fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction("Open File", this, &MainWindow::openFile);
    fileMenu->addAction("Close", this, &MainWindow::closeFile);
    fileMenu->addAction("Export Data", this, &MainWindow::exportData);
    fileMenu->addAction("Print", this, &MainWindow::print);
    fileMenu->addAction("Setting", this, &MainWindow::openSettings);
    fileMenu->addSeparator();
    fileMenu->addAction("Exit", this, &MainWindow::exitApp);

    QMenu *deviceMenu = menuBar()->addMenu("Device");
    deviceMenu->addAction("Open Port", this, &MainWindow::openPort);
    deviceMenu->addAction("Disconnect Port", this, &MainWindow::disconnectPort);
    deviceMenu->addAction("Discover", this, &MainWindow::discoverDevices);
    deviceMenu->addAction("Start Reading Data / Stop", this, &MainWindow::toggleReading);

    QMenu *readingMenu = menuBar()->addMenu("Reading Data");
    readingMenu->addAction("Start Recording Data / Stop", this, &MainWindow::toggleRecording);

    QMenu *recordingMenu = menuBar()->addMenu("Recording Data");
    recordingMenu->addAction("Configure", this, &MainWindow::configureDevice);
    recordingMenu->addAction("Calibrate", this, &MainWindow::calibrateDevice);
    recordingMenu->addAction("Update Firmware", this, &MainWindow::updateFirmware);

    QMenu *viewMenu = menuBar()->addMenu("View");
    viewMenu->addAction("Data Graphs Window", this, &MainWindow::openGraphsWindow);
    viewMenu->addAction("3D Visualizer Window", this, &MainWindow::open3DVisualizerWindow);
    viewMenu->addAction("Data View Window", this, &MainWindow::openDataViewWindow);
    viewMenu->addAction("Device Status Window", this, &MainWindow::openDeviceStatusWindow);
    viewMenu->addSeparator();
    viewMenu->addAction("Tile Windows", this, &MainWindow::tileWindows);
    viewMenu->addAction("Cascade Windows", this, &MainWindow::cascadeWindows);
    viewMenu->addAction("Minimize All Windows", this, &MainWindow::minimizeAllSubWindows);
    viewMenu->addAction("Reset Windows", this, &MainWindow::resetLayout);

    QMenu *helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction("Documentation", this, &MainWindow::openDocumentation);
    helpMenu->addAction("Support", this, &MainWindow::openSupport);
    helpMenu->addAction("About", this, &MainWindow::openAbout);
}

void MainWindow::setupToolBar() {
    QToolBar *toolBar = addToolBar("Main Toolbar");
    toolBar->addAction("Open File", this, &MainWindow::openFile);
    toolBar->addAction("Close File", this, &MainWindow::closeFile);
    toolBar->addAction("Export", this, &MainWindow::exportData);
    toolBar->addSeparator();
    toolBar->addAction("Open Port", this, &MainWindow::openPort);
    toolBar->addAction("Disconnect Port", this, &MainWindow::disconnectPort);
    toolBar->addAction("Discover", this, &MainWindow::discoverDevices);
    toolBar->addAction("Play", this, &MainWindow::toggleReading);
    toolBar->addAction("Record", this, &MainWindow::toggleRecording);
    toolBar->addAction("Stop", this, &MainWindow::resetLayout);
    toolBar->addAction("Configure", this, &MainWindow::configureDevice);
    toolBar->addSeparator();
    toolBar->addAction("Graphs", this, &MainWindow::openGraphsWindow);
    toolBar->addAction("3D Object", this, &MainWindow::open3DVisualizerWindow);
    toolBar->addAction("Data View", this, &MainWindow::openDataViewWindow);
    toolBar->addAction("Device Status", this, &MainWindow::openDeviceStatusWindow);
}

void MainWindow::setupTaskBar() {
    taskBarWidget->setStyleSheet("background-color: #ddd;");
}

void MainWindow::createPositionedSubWindows() {
    QStringList names = { "Data Graphs", "3D Visualizer", "Data View", "Device Status" };

    for (const QString &name : names) {
        QWidget *content = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout(content);

        if (name == "Data View") {
            series = new QLineSeries();
            chart = new QChart();
            chart->legend()->hide();
            chart->addSeries(series);
            chart->createDefaultAxes();
            chart->axisX()->setRange(0, 100);
            chart->axisY()->setRange(0, 105); // Assuming 10-bit ADC Arduino data

            chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            layout->addWidget(chartView);
        }


        content->setLayout(layout);
        QMdiSubWindow *sub = mdiArea->addSubWindow(content);
        sub->setWindowTitle(name);
        sub->resize(400, 300);
        sub->show();
        addMinimizeContext(sub);
    }

    mdiArea->tileSubWindows();
}

void MainWindow::addMinimizeContext(QMdiSubWindow *subWindow) {
    QAction *minimizeAct = new QAction("Minimize", subWindow);
    subWindow->addAction(minimizeAct);
    subWindow->setContextMenuPolicy(Qt::ActionsContextMenu);
    connect(minimizeAct, &QAction::triggered, this, [this, subWindow]() {
        minimizeSubWindow(subWindow);
    });
}

void MainWindow::minimizeSubWindow(QMdiSubWindow *subWin) {
    subWin->hide();
    QPushButton *btn = new QPushButton(subWin->windowTitle(), taskBarWidget);
    taskBarLayout->addWidget(btn);
    taskBarButtons[btn] = subWin;
    connect(btn, &QPushButton::clicked, this, &MainWindow::restoreSubWindow);
}

void MainWindow::restoreSubWindow() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn || !taskBarButtons.contains(btn)) return;

    QMdiSubWindow *subWin = taskBarButtons[btn];
    subWin->showNormal();
    subWin->show();

    taskBarLayout->removeWidget(btn);
    btn->deleteLater();
    taskBarButtons.remove(btn);
}

#define DEFINE_SLOT(name) void MainWindow::name() { qDebug() << #name " triggered"; }
DEFINE_SLOT(closeFile)
DEFINE_SLOT(exportData)
DEFINE_SLOT(print)
DEFINE_SLOT(openSettings)
DEFINE_SLOT(exitApp)
DEFINE_SLOT(discoverDevices)
DEFINE_SLOT(toggleReading)
DEFINE_SLOT(toggleRecording)
DEFINE_SLOT(configureDevice)
DEFINE_SLOT(calibrateDevice)
DEFINE_SLOT(updateFirmware)
DEFINE_SLOT(openGraphsWindow)
DEFINE_SLOT(open3DVisualizerWindow)
DEFINE_SLOT(openDataViewWindow)
DEFINE_SLOT(openDeviceStatusWindow)
DEFINE_SLOT(openDocumentation)
DEFINE_SLOT(openSupport)
DEFINE_SLOT(openAbout)

void MainWindow::openFile() {
    qDebug() << "Open File triggered";
}



void MainWindow::openPort() {
    if (serial->isOpen()) {
        serial->close();
    }

    PortDialog dialog(this);
    if (dialog.exec() != QDialog::Accepted)
        return;

    QString portName = dialog.selectedPort();
    if (portName.isEmpty()) {
        QMessageBox::warning(this, "No Port", "No port selected.");
        return;
    }

    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!serial->open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Failed to open port.");
    } else {
        QMessageBox::information(this, "Port Opened", "Connected to " + portName);
    }
}
void MainWindow::disconnectPort() {
    if (serial->isOpen()) {
        serial->close();
        QMessageBox::information(this, "Disconnected", "Serial port disconnected.");
    } else {
        QMessageBox::information(this, "Info", "No serial port is currently open.");
    }
}


void MainWindow::cascadeWindows() {
    for (auto win : mdiArea->subWindowList()) {
        if (win->isHidden()) win->show();
    }
    mdiArea->cascadeSubWindows();
}

void MainWindow::tileWindows() {
    for (auto win : mdiArea->subWindowList()) {
        if (win->isHidden()) win->show();
    }
    mdiArea->tileSubWindows();
}

void MainWindow::minimizeAllSubWindows() {
    for (auto win : mdiArea->subWindowList()) {
        if (!win->isHidden()) minimizeSubWindow(win);
    }
}

void MainWindow::resetLayout() {
    QSize mdiSize = mdiArea->size();
    int w = mdiSize.width() / 2;
    int h = mdiSize.height() / 2;

    QPoint positions[] = {
        QPoint(0, 0), QPoint(w, 0),
        QPoint(0, h), QPoint(w, h)
    };

    int i = 0;
    for (QMdiSubWindow *win : mdiArea->subWindowList()) {
        if (win->isHidden()) win->show();
        if (i < 4) {
            win->resize(w - 20, h - 20);
            win->move(positions[i]);
        }
        ++i;
    }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    resetLayout();
}
