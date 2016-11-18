#include "cpu.h"

CPU::CPU()
{
    this->cpuTotal.append(100);
    this->cpuUsage.append(100);
    this->numCPUs = 0;
}

bool CPU::openFile(){
    QFile memFile("/proc/stat");

    if (memFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->content = memFile.readAll();
        memFile.close();
        return true;
    }
    return false;
}

void CPU::concatenate(){
    if(this->openFile()){
        QStringList lines = this->content.split("\n");
        QStringList column;

        // LER ATÉ AS QUE NÃO COMEÇAM COM cpu
        for(int i = 1; i < lines.size(); i++){
            column = lines.at(i).split(" ");
            if(column.at(0).contains("cpu")){
                this->prevCpuUsage = this->cpuUsage;
                this->prevCpuTotal = this->cpuTotal;
                this->cpuUsage.append(column.at(1).toLong() + column.at(2).toLong() + column.at(3).toLong());
                this->cpuTotal.append(column.at(1).toLong() + column.at(2).toLong() + column.at(3).toLong() + column.at(4).toLong() + column.at(5).toLong() );
                this->numCPUs++;
            }
            else{
                break;
            }
        }
    }
}

void CPU::calculate(){

    if(this->openFile()){
        QStringList lines = this->content.split("\n");
        QStringList column;
        double data;
        for(int i = 1; i <= this->numCPUs; i++){
            column = lines.at(i).split(" ");
            this->prevCpuUsage[i-1] = this->cpuUsage[i-1];
            this->prevCpuTotal[i-1] = this->cpuTotal[i-1];
            this->cpuUsage.append(column.at(1).toInt() + column.at(2).toInt() + column.at(3).toInt());
            this->cpuTotal.append(column.at(1).toInt() + column.at(2).toInt() + column.at(3).toInt() + column.at(4).toInt() + column.at(5).toInt() );
            data = ((this->cpuUsage.at(i-1) - this->prevCpuUsage.at(i-1))*100.0)/(this->cpuTotal.at(i-1) - this->prevCpuTotal.at(i-1) + 1);
            this->dataCpus.append(i*10);
        }
    }
}

int CPU::getNumCPUs(){
    return this->numCPUs;
}

QVector<double> CPU::getData(){
    return this->dataCpus;
}
