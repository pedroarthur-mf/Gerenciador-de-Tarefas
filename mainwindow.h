#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <cstdlib>
#include "memory.h"
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

public slots:
    void realtimeDataSlot();

private:
    Ui::MainWindow *ui;
    QTimer dataTimer;
    Memory memory;
    Supply supply;
};

#endif // MAINWINDOW_H
