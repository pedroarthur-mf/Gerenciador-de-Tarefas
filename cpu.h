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
    void concatenate();
    QVector<int> cpuUsage;
    QVector<int> cpuTotal;
    QVector<int> prevCpuUsage;
    QVector<int> prevCpuTotal;


public:
    CPU();
    int getNumCPUs();
    void calculate();
};

#endif // CPU_H
