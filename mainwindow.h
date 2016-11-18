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
    void run();

signals:
    void signalMemoryGraph();
    void signalCPUGraph();
    void signalSupplyGraph();

private slots:
    void slotMemoryGraph();
    void slotCPUGraph();
    void slotSupplyGraph();

private:
    Ui::MainWindow *ui;
    bool firstTime;
    QTimer dataTimer;

    std::thread thMemory;
    std::thread thCPU;
    std::thread thSupply;

    Memory memory;
    CPU cpu;
    Supply supply;

    void memoryGraph();
    void CPUGraph();
    void SupplyGraph();
};

#endif // MAINWINDOW_H
