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
//    QVector<long double> dataCpus;

public:
    CPU();
    int getNumCPUs();
    void calculate();
    void concatenate();
//    QVector<long double> getData();
    double getDataCPU(int i);
};

#endif // CPU_H
