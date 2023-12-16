#pragma once
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using graph_type = std::unordered_map<uint32_t, std::vector<std::pair<uint32_t, uint8_t>>>;

class Serializer {
public:
    Serializer(std::string in, std::string out) : input_file_name(in), output_file_name(out) {
        read();
        write();
    };
private:
    std::string input_file_name;
    std::string output_file_name;
    graph_type graph;
    void read();
    void write();
};
