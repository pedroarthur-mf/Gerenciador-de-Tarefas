#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process
{
private:
    std::string name;
    int pid;
    int ppid;
    double memUsage;
    double cpuUsage;
public:
    double compare;

    Process();
    void setName(std::string);
    void setPid(int);
    void setPpid(int);
    void setMemUsage(double);
    void setCpuUsage(double);
    std::string getName() const;
    int getPid() const;
    int getPpid() const;
    double getMemUsage() const;
    double getCpuUsage() const;
};

#endif // PROCESS_H
