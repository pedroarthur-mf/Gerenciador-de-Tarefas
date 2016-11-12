#include "cpu.h"

CPU::CPU()
{
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
        int i = 0;

        // LER ATÉ AS QUE NÃO COMEÇAM COM cpu
        while(lines[i][0] != 'c' && lines[i][1] != 'p' && lines[i][2] != 'u'){
            // IGNORAR A PRIMEIRA LINHA
            if(i == 0) continue;
        }


        // TODO:
        // VERIFICAR O TAMANHO DE LINES (= NUMERO DE CPUS)
        // CONCATENAR POR ESPAÇO
    }
}
