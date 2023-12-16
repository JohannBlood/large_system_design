#pragma once
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

class Deserializer{
public:
    Deserializer(std::string in, std::string out) : input_file_name(in), output_file_name(out) {
        Deserialization();
    };
private:
    std::string input_file_name;
    std::string output_file_name;
    void Deserialization();
};