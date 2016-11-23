#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <QFile>
#include <QHash>

class Memory
{
public:
    Memory();
    void concatenate();
    double calculateMemory();
    int calculateSwap();
    int getTotal();

private:
    QString content;
    QHash <QString, int> infos;
    bool openFile();
};

#endif // MEMORY_H
