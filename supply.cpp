#include "supply.h"

Supply::Supply(){ }

bool Supply::openFile(){
    QFile memFile("/sys/class/power_supply/BAT1/uevent");

    if (memFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->content = memFile.readAll();
        memFile.close();
        return true;
    }
    return false;
}

//TUDO CERTO, TAMBÉM:
void Supply::concatenate(){
    if( this->openFile()){
        QStringList lines = this->content.split("\n");
        QStringList value;

        for(int i = 0; i < lines.size() - 1; i++){
            value = lines[i].split("=");
            this->infos.insert(value[0].simplified(), value[1].toInt());
        }
    }
}

double Supply::calculateSupply(){
    int full = this->infos.value("POWER_SUPPLY_CHARGE_FULL");
    int now = this->infos.value("POWER_SUPPLY_CHARGE_NOW");

    return (now*100.0)/full;
}

double Supply::timeRemaining(){
    int full = this->infos.value("POWER_SUPPLY_CHARGE_FULL");
    int now = this->infos.value("POWER_SUPPLY_CHARGE_NOW");
    int currentNow = this->infos.value("POWER_SUPPLY_CORRENT_NOW");

    return (full - now)/currentNow;
}
