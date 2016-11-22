#ifndef TOJSON_H
#define TOJSON_H

#include <iostream>
#include <QFile>
#include <QVector>
#include <fstream>
#include <sstream>
#include "process.h"

class toJson
{
private:
    QString content;
    QVector<Process> processos;
    void getProcessData();
public:
    toJson();
    QVector<Process> getData();
    void generateJson();
};

#endif // TOJSON_H
