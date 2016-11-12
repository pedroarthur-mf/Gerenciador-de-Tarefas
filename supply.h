#ifndef CARGA_H
#define CARGA_H

#include <iostream>
#include <QFile>
#include <QHash>

class Supply
{
public:
    Supply();
    void concatenate();
    double calculateSupply();
    double timeRemaining();


private:
    QString content;
    QHash <QString, int> infos;
    bool openFile();
};

#endif // CARGA_H
