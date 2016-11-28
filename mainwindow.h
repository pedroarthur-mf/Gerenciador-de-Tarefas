#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <cstdlib>
#include <thread>
#include <chrono>
#include "memory.h"
#include "cpu.h"
#include "supply.h"
#include "tojson.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void configMemoryGraph();
    void configCPUGraph();
    void configSupplyGraph();
    void configProcGraph();
    void run();

signals:
    void signalMemoryGraph();
    void signalCPUGraph();
    void signalSupplyGraph();
    void signalSupplyRemGraph();
    void signalProcGraph();
    void signalBtnUpd();

private slots:
    void slotMemoryGraph();
    void slotCPUGraph();
    void slotSupplyGraph();
    void slotSupplyRemGraph();
    void slotProcGraph();
    void slotBtnUpd();

    void on_updateButton_clicked();

    void on_killButton_clicked();

private:
    Ui::MainWindow *ui;
    bool firstTime;
    QTimer dataTimer;

    std::thread thMemory;
    std::thread thCPU;
    std::thread thSupply;
    std::thread thSupplyRem;
    std::thread thProc;
    std::thread thBtnUpd;

    Memory memory;
    CPU cpu;
    Supply supply;
    toJson json;

    void memoryGraph();
    void CPUGraph();
    void SupplyGraph();
    void SupplyRemGraph();
    void procGraph();
    void btnUpdate();
};

#endif // MAINWINDOW_H
