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
#include <unordered_map>

class Solver {
   protected:
    std::fstream file;
    std::string fileInput;

   public:
    Solver() {}

    Solver(const std::string &_fileInput) : fileInput(_fileInput) {
        this->file.open(_fileInput);
    }

    virtual ~Solver() { this->file.close(); };

    void Print(std::string &str) { std::cout << str << std::endl; }

    int Solve_Day01_part1();
    int Solve_Day01_part2();

    int Solve_Day02_part1();
    int Solve_Day02_part2();

    long Solve_Day03_part1();
    long Solve_Day03_part2();

    int Solve_Day04_part1();
    int Solve_Day04_part2();

    long Solve_Day06_part1();
    long Solve_Day06_part2();

    long Solve_Day07_part1();
    long Solve_Day07_part2();

    long Solve_Day09_part1();
    long Solve_Day09_part2();
};

#endif  // UTILS2024_H
