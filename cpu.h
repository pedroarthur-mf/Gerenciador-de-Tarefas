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

public:
    CPU();
};

#endif // CPU_H
