#ifndef TOJSON_H
#define TOJSON_H

#include <iostream>
#include <map>
#include <vector>
#include <QString>
#include <fstream>
#include <sstream>

#include "process.h"

#define PATH "/home/pedroarthur-mf/Gerenciador-de-Tarefas/"

class toJson
{
private:
    QString content;
    std::map<int, std::vector<Process>> process;
    void getProcessData(int);
public:
    toJson();
    void generateJson(int);
    void update(int);
};

#endif // TOJSON_H
