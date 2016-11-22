#include "tojson.h"

toJson::toJson()
{

}

void toJson::getProcessData(){
    system("ps xao comm,pid,ppid,%mem,%cpu > datafile.txt");

    std::ifstream dataFile("datafile.txt");
    if (!dataFile.is_open()) {
        exit(1);
    }

    std::string lines;
    std::getline(dataFile, lines);

    while (std::getline(dataFile, lines)) {
        Process temp;
        std::stringstream ss(lines);
        std::string name;
        int pid, ppid;
        double cpu, mem;
        ss >> name >> pid >> ppid >> mem >> cpu;

        temp.setName(name);
        temp.setPid(pid);
        temp.setPpid(ppid);
        temp.setMemUsage(mem);
        temp.setCpuUsage(cpu);

        // Jogar as coisas para dentro de outra TAD (if ppid == 0 -> chave,  else informação)
        processos.append(temp);
    }

    dataFile.close();
}

QVector<Process> toJson::getData(){
    this->getProcessData();
    return this->processos;
}
 void toJson::generateJson(){
    std::ofstream file ("test.json");
    if(file.is_open()){

        // ESCREVER NO ARQUIVO (RECURSIVO?)

        file.close();
    }
 }
