#include "serializer.h"
#include "deserializer.h"

int main(int argc, char* argv[]) {    
    std::string input_file_name, output_file_name;
    bool fl;
    for(int i = 1; i < argc; ++i) {
        auto arg = std::string(argv[i]);
        if(arg == "-d")
            fl = false;
        else if(arg == "-s")
            fl = true;
        else if(arg == "-i")
            input_file_name = std::string(argv[++i]);
        else if(arg == "-o")
            output_file_name = std::string(argv[++i]);
        else {
            std::cout << "No such parameter" << std::endl;
            return 1;
        }
    }
    if(fl)
        Serializer serial(input_file_name, output_file_name);
    else
        Deserializer deserial(input_file_name, output_file_name);
    return 0;
}       