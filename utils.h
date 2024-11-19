#ifndef UTILS_H
#define UTILS_H

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
  Solver() {}
  Solver(const std::string &_fileInput) : fileInput(_fileInput) {
    this->file.open(_fileInput);
  }
  virtual ~Solver() { this->file.close(); };

  void Print(std::string &str) { std::cout << str << std::endl; }

  long Solve_day_9_part1();
  long Solve_day_9_part2();

  int Solve_day_10_part1();
  int Solve_day_10_part2();

  int Solve_day_11_part1();
  int Solve_day_11_part2();

  int Solve_day_12_part1();
  int Solve_day_12_part2();
};

#endif
