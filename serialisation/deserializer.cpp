#include "deserializer.h"

void Deserializer::Deserialization(){
    std::ifstream in(input_file_name, std::ios_base::binary);
    std::ofstream out(output_file_name);
    uint32_t id1, id2, size, edges_num;
    uint8_t weight;
    in.read(reinterpret_cast<char*>(&edges_num), sizeof(edges_num));

    for(uint32_t iter = 0; iter < edges_num; ++iter){
        in.read(reinterpret_cast<char*>(&id1), sizeof(id1));
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        for(int i = 0; i < size; ++i){
            in.read(reinterpret_cast<char*>(&id2), sizeof(id2));
            in.read(reinterpret_cast<char*>(&weight), sizeof(weight));
            out << id1 << '\t' << id2 << '\t' << (int)weight << '\n';
        }
    }
    out.close();
    in.close();
}