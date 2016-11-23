#include "tojson.h"


// TODO: Arrumar o UPDATE e as métricas (ta meio estranho).
toJson::toJson()
{

}

void toJson::getProcessData(int comp){
    system("ps xao pid,ppid,%mem,%cpu,comm > datafile.txt");

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
        ss >> pid >> ppid >> mem >> cpu;

        temp.setPid(pid);
        temp.setPpid(ppid);
        temp.setMemUsage(mem);
        temp.setCpuUsage(cpu);

        if(ss >> name){
            temp.setName(name);
        }

        switch (comp) {
        case 0:
            temp.compare = temp.getMemUsage() * 10;
            break;
        case 1:
            temp.compare = temp.getCpuUsage() * 10;
            break;
        default:
            temp.compare = 100;
            break;
        }
        this->process[temp.getPpid()].push_back(temp);
    }
    dataFile.close();
}

 void toJson::generateJson(int comp){
    this->getProcessData(comp);

     std::ostringstream oss;
    std::ofstream jsonFile(std::string(PATH) + "test.json", std::ios::trunc);

    // ARQUIVO:
    oss << "{\"name\": \"processos\", \"children\": [";

    int i = 0;
    for(auto e : process){
        // FAMÍLIA:
        if(i != 0){
            oss << ",";
        }
        oss << "{\"name\": \"default " << i << "\", \"children\": [";

        int j = 0;
        for(auto p : e.second){
            // FILHOS:
            if(j != 0){
                oss << ",";
            }
            oss << "{\"name\": \"" << p.getName() << "\", \"size\": " << p.compare << ", \"pid\": " << p.getPid() <<  "}";
            j++;
        }
        oss << "]}";
        i++;
    }
    oss << "]}";

    std::string json_final = oss.str();
    jsonFile << json_final << "\n";
    jsonFile.close();
 }

 void toJson::update(int comp){
    process.clear();
    generateJson(comp);
 }

