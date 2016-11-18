#include "cpu.h"

CPU::CPU()
{
    this->numCPUs = 0;

    if(this->openFile()){
        QStringList lines = this->content.split("\n");
        QStringList column;
        for(int i = 1; i < lines.size(); i++){
            column = lines.at(i).split(" ");
            if(column.at(0).contains("cpu")){
//                this->cpuUsage.append(column.at(1).toLong() + column.at(2).toLong() + column.at(3).toLong());
//                this->cpuTotal.append(column.at(1).toLong() + column.at(2).toLong() + column.at(3).toLong() + column.at(4).toLong() + column.at(5).toLong() );
                cpuIdle.append(column.at(1).toInt() + column.at(2).toInt() + column.at(3).toInt());
                cpuTime.append(column.at(1).toInt() + column.at(2).toInt() + column.at(3).toInt() + column.at(4).toInt() + column.at(5).toInt());
                this->numCPUs++;
            }else{
                break;
            }
        }
    }

    this->prevCpuIdle.resize(this->numCPUs);
    this->prevCpuTime.resize(this->numCPUs);
}

bool CPU::openFile(){
    QFile cpuFile("/proc/stat");

    if (cpuFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->content = cpuFile.readAll();
        cpuFile.close();
        return true;
    }
    return false;
}

void CPU::calculate(){
    if(openFile()){
        QStringList lines = this->content.split("\n");
        QStringList column;
        for(int i = 1; i < lines.size() - 1; i++){
            if(i > numCPUs) break;
            prevCpuIdle[i-1] = cpuIdle[i-1];
            prevCpuTime[i-1] = cpuTime[i-1];

            column = lines.at(i).split(" ");

            cpuIdle[i-1] = column.at(1).toInt() + column.at(2).toInt() + column.at(3).toInt();
            cpuTime[i-1] = cpuIdle.at(i-1) + column.at(4).toInt() + column.at(5).toInt();

        }
    }
}

double CPU::getDataCPU(int i){
    return ((cpuIdle.at(i) - prevCpuIdle.at(i))*100)/(cpuTime.at(i) - prevCpuTime.at(i) + 1);
}

int CPU::getNumCPUs(){
    return this->numCPUs;
}

