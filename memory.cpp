#include "memory.h"

Memory::Memory()
{
}

//TUDO CERTO:
bool Memory::openFile(){
    QFile memFile("/proc/meminfo");

    if (memFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->content = memFile.readAll();
        memFile.close();
        return true;
    }
    return false;
}

//TUDO CERTO, TAMBÉM:
void Memory::concatenate(){
    if( this->openFile()){
        QStringList lines = this->content.split("\n");
        QStringList value;

        for(int i = 0; i < lines.size() - 1; i++){
            value = lines[i].split(":");
            this->infos.insert(value[0].simplified(), value[1].simplified().remove("kB").toInt());
        }
    }
}

double Memory::calculateMemory(){
    int total = this->infos.value("MemTotal");
    int used = this->infos.value("MemAvailable");

    return ((total - used)*100.0)/total;

}

int Memory::calculateSwap(){
    int total = this->infos.value("SwapTotal");
    int used = this->infos.value("SwapFree");

    return ((total - used)*100.0)/total;
}
