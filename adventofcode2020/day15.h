#ifndef DAY15_H
#define DAY15_H

#ifndef UTILS_H
#include "utils2020.h"
#endif

#include <unordered_map>

int Solver::Solve_day_15(long target) {
  std::string number;
  std::unordered_map<int, int> memory;
  int currentPosition = 1;
  int currentNumber;
  int previousNumber = -1;

  std::getline(file, number, ',');
  previousNumber = std::stoi(number);
  while (std::getline(file, number, ',')) {
    memory[previousNumber] = currentPosition;
    previousNumber = std::stoi(number);
    ++currentPosition;
  }
  while (currentPosition < target) {
    if (memory[previousNumber] == 0) {
      currentNumber = 0;
    } else {
      currentNumber = currentPosition - memory[previousNumber];
    }
    memory[previousNumber] = currentPosition;
    previousNumber = currentNumber;
    ++currentPosition;
  }
  return currentNumber;
}

#endif
