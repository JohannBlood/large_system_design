#include "serializer.h"

void Serializer::read() {
    graph_type new_graph;

    std::ifstream in(input_file_name);
    std::string line;
    uint32_t id1, id2, buf;
    uint8_t weight;
    while(std::getline(in, line)) {
        std::istringstream s(line);
        s >> id1 >> id2 >> buf;
        weight = static_cast<uint8_t>(buf);
        if(id1 != id2) {
            new_graph[id1].push_back({id2, weight});
            new_graph[id2].push_back({id1, weight});
        }else {
            new_graph[id1].push_back({id2, weight});
        }
    }
    in.close();

    std::unordered_set<uint32_t> visited;
    for(const auto& [key, value]: new_graph) {
        std::vector<std::pair<uint32_t, uint8_t>> neighbours;
        for(auto edge: value) {
            if(!visited.count(edge.first)) {
                neighbours.push_back(edge);
            }
        }
        if(neighbours.empty())
            continue;
        visited.insert(key);
        graph[key] = neighbours;
    }
}


void Serializer::write() {
    std::ofstream out(output_file_name, std::ios_base::binary);
    uint32_t len = static_cast<uint32_t>(graph.size());
    out.write(reinterpret_cast<char*>(&len), sizeof(len));
    for(auto it = graph.begin(); it != graph.end(); ++it) {
        auto id = it->first;
        uint32_t size = it->second.size();
        out.write(reinterpret_cast<char*>(&id), sizeof(id));
        out.write(reinterpret_cast<char*>(&size), sizeof(size));
        for (auto& el: it->second) {
            auto id2 = el.first;
            auto w = el.second;
            out.write(reinterpret_cast<char*>(&id2), sizeof(id2));
            out.write(reinterpret_cast<char*>(&w), sizeof(w));
        }
    }
    out.close();
}