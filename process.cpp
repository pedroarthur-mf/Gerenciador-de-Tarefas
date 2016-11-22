#include "process.h"

Process::Process()
{
//    this->name = name;
//    this->pid = pid;
//    this->ppid = ppid;
//    this->memUsage = mem;
//    this->cpuUsage = cpu;
}

void Process::setName(std::string name){
    this->name = name;
}

void Process::setPid(int pid){
    this->pid = pid;
}

void Process::setPpid(int ppid){
    this->ppid = ppid;
}

void Process::setMemUsage(double mem){
    this->memUsage = mem;
}

void Process::setCpuUsage(double cpu){
    this->cpuUsage = cpu;
}

std::string Process::getName() const{
    return this->name;
}

int Process::getPid() const{
    return this->pid;
}

int Process::getPpid() const{
    return this->ppid;
}

double Process::getMemUsage() const{
    return this->memUsage;
}

double Process::getCpuUsage() const{
    return this->cpuUsage;
}
