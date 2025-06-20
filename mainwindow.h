#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QPushButton>
#include <QMap>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QSerialPort>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_USE_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    // File
    void openFile();
    void closeFile();
    void exportData();
    void print();
    void openSettings();
    void exitApp();

    // Device
    void openPort();
    void discoverDevices();
    void toggleReading();
    void disconnectPort();

    // Reading Data
    void toggleRecording();

    // Recording Data
    void configureDevice();
    void calibrateDevice();
    void updateFirmware();

    // View Windows
    void openGraphsWindow();
    void open3DVisualizerWindow();
    void openDataViewWindow();
    void openDeviceStatusWindow();

    // Window Management
    void cascadeWindows();
    void tileWindows();
    void minimizeAllSubWindows();
    void resetLayout();

    // Help
    void openDocumentation();
    void openSupport();
    void openAbout();

    void restoreSubWindow();
    void minimizeSubWindow(QMdiSubWindow *subWin);

private:
    QMdiArea *mdiArea;
    QWidget *taskBarWidget;
    QHBoxLayout *taskBarLayout;
    QMap<QPushButton*, QMdiSubWindow*> taskBarButtons;

    QSerialPort *serial;
    QPlainTextEdit *dataViewEdit;



    // Chart-related
    QChart *chart = nullptr;
    QChartView *chartView = nullptr;
    QLineSeries *series = nullptr;

    // Data point index (x-axis)
    int dataPointIndex = 0;

    void setupMenuBar();
    void setupToolBar();
    void setupTaskBar();
    void createPositionedSubWindows();
    void addMinimizeContext(QMdiSubWindow *subWindow);
};

#endif // MAINWINDOW_H
