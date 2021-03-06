#include "tojson.h"


// TODO: Arrumar o UPDATE e as métricas (ta meio estranho).
toJson::toJson()
{

}

void toJson::getProcessData(int comp){
    process.clear();
    system("ps xao pid,ppid,%mem,%cpu,nlwp,comm > datafile.txt");

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
        double cpu, mem,thusage;
        ss >> pid >> ppid >> mem >> cpu >> thusage;

        temp.setPid(pid);
        temp.setPpid(ppid);
        temp.setMemUsage(mem);
        temp.setCpuUsage(cpu);
        temp.setThUsage(thusage);

        if(ss >> name){
            temp.setName(name);
        }

        switch (comp) {
        case 0:
            temp.compare = (temp.getMemUsage()+0.01);
            break;
        case 1:
            temp.compare = (temp.getCpuUsage()+0.01);
            break;
        case 2:
            temp.compare = temp.getThUsage();
            break;
        case 3:
            temp.compare = ((temp.getMemUsage()+0.01))+((temp.getCpuUsage()+0.01))/2;
        }
        this->process[temp.getPpid()].push_back(temp);
    }
    dataFile.close();
}

void toJson::generateJson(int comp){
    this->getProcessData(comp);

    std::ostringstream oss;
    std::ofstream jsonFile(std::string(PATH) + "procs.json", std::ios::trunc);

    // ARQUIVO:
    oss << "{\n \"name\": \"processos\",\n \"children\":\n [\n";

    int i = 0;
    for(auto e : process){
        // FAMÍLIA:
        if(i != 0){
            oss << ",\n";
        }
        oss << "  {\n    \"name\": \"default " << i << "\",\n    \"children\":\n    [\n";

        int j = 0;
        for(auto p : e.second){
            // FILHOS:
            if(j != 0){
                oss << ",\n";
            }
            oss << "      {\"name\": \"" << p.getName() << "\", \"size\": " << p.compare << ", \"pid\": " << p.getPid() <<  "}";
            j++;
        }
        oss << "\n    ]\n  }";
        i++;
    }
    oss << "\n ]\n}";

    std::string json_final = oss.str();
    jsonFile << json_final << "\n";
    jsonFile.close();
}

void toJson::update(int comp){
    generateJson(comp);
}

