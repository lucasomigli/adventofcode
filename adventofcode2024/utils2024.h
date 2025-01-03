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
#include <unordered_set>

class Solver {
   protected:
    std::fstream file;
    std::string fileInput;

   public:
    Solver() {}

    Solver(const std::string& _fileInput) : fileInput(_fileInput) {
        this->file.open(_fileInput);

        std::cout << "Input file: " << _fileInput << std::endl;
    }

    virtual ~Solver() { this->file.close(); };

    void Print(std::string& str) { std::cout << str << std::endl; }

    int Solve_Day01_part1();
    int Solve_Day01_part2();

    int Solve_Day02_part1();
    int Solve_Day02_part2();

    long Solve_Day03_part1();
    long Solve_Day03_part2();

    int Solve_Day04_part1();
    int Solve_Day04_part2();

    long Solve_Day05_part1();
    long Solve_Day05_part2();

    long Solve_Day06_part1();
    long Solve_Day06_part2();

    long Solve_Day07_part1();
    long Solve_Day07_part2();

    long Solve_Day08_part1();
    long Solve_Day08_part2();

    long Solve_Day09_part1();
    long Solve_Day09_part2();

    long Solve_Day10_part1();
    long Solve_Day10_part2();

    long Solve_Day11_part1();
    long Solve_Day11_part2();

    long Solve_Day12_part1();
    long Solve_Day12_part2();

    int Solve_Day13_part1();
    long Solve_Day13_part2();
};

namespace utils {

struct Point {
    int x, y;
    char c = '.';
    bool checked = false;
    Point(int _x, int _y) : x(_x), y(_y) {};
    Point(int _x, int _y, char _c) : x(_x), y(_y), c(_c) {};
    bool operator==(const Point& right) const { return (x == right.x) && (y == right.y); }
    bool operator<(const Point& right) const {
        if (x == right.x) {
            return y < right.y;
        }
        return x < right.x;
    }
};

void PrintGrid(std::map<std::pair<int, int>, Point> _grid, std::pair<int, int> _gridSize) {
    for (size_t y = 0; y < _gridSize.second; ++y) {
        std::string out = "";
        for (size_t x = 0; x < _gridSize.first; ++x) {
            out += _grid.at({x, y}).c;
        }
        std::cout << out << std::endl;
    }
};
}  // namespace utils

#endif  // UTILS2024_H
