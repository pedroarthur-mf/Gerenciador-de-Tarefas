#ifndef CPU_H
#define CPU_H

#include <QFile>
#include <QVector>

class CPU
{
private:
    int numCPUs;
    QString content;
    bool openFile();
    QVector<long> cpuUsage;
    QVector<long> cpuTotal;
    QVector<long> prevCpuUsage;
    QVector<long> prevCpuTotal;
    QVector<double> dataCpus;


public:
    CPU();
    int getNumCPUs();
    void calculate();
    void concatenate();
    QVector<double> getData();
};

#endif // CPU_H
