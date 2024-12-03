#ifndef UTILS2024_H
#define UTILS2024_H

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>
#include <set>
#include <sstream>
#include <unordered_set>

class Solver {
protected:
    std::fstream file;
    std::string fileInput;

public:
    Solver() {
    }

    Solver(const std::string &_fileInput) : fileInput(_fileInput) {
        this->file.open(_fileInput);
    }

    virtual ~Solver() { this->file.close(); };

    void Print(std::string &str) { std::cout << str << std::endl; }

    int Solve_Day01_part1();

    int Solve_Day01_part2();

    int Solve_Day02_part1();

    int Solve_Day02_part2();
};

#endif //UTILS2024_H
