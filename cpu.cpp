#include "cpu.h"

CPU::CPU()
{
    // TODO: Preencher o atual com qualquer coisa pra começar aqui diferente de errado.
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
        int i = 0;
        this->numCPUs = 0;

        // LER ATÉ AS QUE NÃO COMEÇAM COM cpu
        while(lines[i][0] != 'c' && lines[i][1] != 'p' && lines[i][2] != 'u'){
            // IGNORAR A PRIMEIRA LINHA
            if(i == 0) continue;
            column = lines.at(i).split(" ");
            this->prevCpuUsage = this->cpuUsage;
            this->prevCpuTotal = this->cpuTotal;
            this->cpuUsage.append(column.at(1).toInt() + column.at(2).toInt() + column.at(3).toInt());
            this->cpuTotal.append(column.at(1).toInt() + column.at(2).toInt() + column.at(3).toInt() + column.at(4).toInt() + column.at(5).toInt() );
            i++;
            this->numCPUs++;
        }
    }
}

void CPU::calculate(){
    // Tem o que ter o valor anterior
    // (O que ta usando do atual - o que ta usando do anterior)/(O total do atual - o total do anterior)
}

int CPU::getNumCPUs(){
    return this->numCPUs;
}
