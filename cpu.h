#ifndef CPU_H
#define CPU_H

#include <QFile>
#include <QVector>
#include <iostream>

class CPU
{
private:
    int numCPUs;
    QString content;
    bool openFile();
    QVector<long> cpuTime;
    QVector<long> cpuIdle;
    QVector<long> prevCpuTime;
    QVector<long> prevCpuIdle;

public:
    CPU();
    int getNumCPUs();
    void calculate();
    void concatenate();
    double getDataCPU(int i);
};

#endif // CPU_H
