#include <iostream>
#include <map>
#include <chrono>
#include <fstream>

// Вставка элементов, упорядоченных по возрастанию ключа, подсказка - итератор, указывающий на конец контейнера.
void test_1(std::ofstream& outFile){
    // Пример 1: Вставка элементов с использованием hint
    std::map<int, std::string> myMap1;
    auto start1 = std::chrono::high_resolution_clock::now();
    auto hint = myMap1.begin();
    for (int i = 0; i < 100000; ++i) {
        myMap1.insert(hint, std::make_pair(i, "value"));
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    outFile << "Тест 1 (с подсказкой): " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count() << " мкс" << std::endl;

    // Пример 2: Вставка элементов без использования hint
    std::map<int, std::string> myMap2;
    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        myMap2.insert(std::make_pair(i, "value"));
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    outFile << "Тест 1 (без подсказкой): " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count() << " мкс" << std::endl;
}

// Вставка элементов, упорядоченных по убыванию ключа, подсказка - итератор, указывающий на начало контейнера.
void test_2(std::ofstream& outFile){
    // Пример 1: Вставка элементов с использованием hint
    std::map<int, std::string> myMap1;
    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 100000; i > 0; --i) {
        auto hint = myMap1.begin();
        myMap1.insert(hint, std::make_pair(i, "value"));
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    outFile << "Тест 2 (с подсказкой): " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count() << " мкс" << std::endl;

    // Пример 2: Вставка элементов без использования hint
    std::map<int, std::string> myMap2;
    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 100000; i > 0; --i) {
        myMap2.insert(std::make_pair(i, "value"));
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    outFile << "Тест 2 (без подсказкой): " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count() << " мкс" << std::endl;
}

int main() {
    const char* filename = "res.txt";
    std::ofstream outFile(filename, std::ios::app);

    test_1(outFile);
    test_2(outFile);

    outFile.close();

    return 0;
}
