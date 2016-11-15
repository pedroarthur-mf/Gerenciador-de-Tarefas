#include "supply.h"

Supply::Supply(){ }

bool Supply::openFile(){
    QFile supplyFile("/sys/class/power_supply/BAT1/uevent");

    if(!supplyFile.exists()){
       supplyFile.setFileName("/sys/class/power_supply/BAT0/uevent");
    }

    if (supplyFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->content = supplyFile.readAll();
        supplyFile.close();
        return true;
    }
    return false;
}

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
    double now = this->infos.value("POWER_SUPPLY_CHARGE_NOW");
    double currentNow = this->infos.value("POWER_SUPPLY_CURRENT_NOW");
    return now/currentNow;
}
