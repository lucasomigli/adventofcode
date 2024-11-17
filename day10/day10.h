#ifndef UTILS_H
#include "../utils.h"
#endif

int Solver::Solve_day_10_part2() {
  std::string line;
  std::set<int> memory;
  int newValue;
  std::pair<int, int> joltsCount = {0, 0};

  // Load into memory
  while (std::getline(file, line)) {
    newValue = std::stoi(line);
    memory.insert(newValue);
  }

  std::set<int>::iterator it = memory.begin();
  int difference = *it;

  int currentValue;
  int prevValue;
  for (it = memory.begin(); it != memory.end(); it++) {
    if (it != memory.begin()) {
      currentValue = *it;
      it--;
      prevValue = *it;
      it++;
      difference = currentValue - prevValue;
    }

    if (std::abs(difference) == 1) {
      joltsCount.first += 1;
    } else if (std::abs(difference) == 3) {
      joltsCount.second += 1;
    }
  }

  joltsCount.second += 1;

  return joltsCount.first * joltsCount.second;
};

int Solver::Solve_day_10_part1() {
  std::string line;
  std::set<int> memory;
  int newValue;
  std::pair<int, int> joltsCount = {0, 0};

  // Load into memory
  while (std::getline(file, line)) {
    newValue = std::stoi(line);
    memory.insert(newValue);
  }

  std::set<int>::iterator it = memory.begin();
  int difference = *it;
  std::cout << difference << std::endl;
  int currentValue;
  int prevValue;
  for (it = memory.begin(); it != memory.end(); it++) {
    if (it != memory.begin()) {
      currentValue = *it;
      it--;
      prevValue = *it;
      it++;
      difference = currentValue - prevValue;
    }

    if (std::abs(difference) == 1) {
      joltsCount.first += 1;
    } else if (std::abs(difference) == 3) {
      joltsCount.second += 1;
    }
    std::cout << difference << " " << currentValue << " " << prevValue
              << std::endl;
  }

  joltsCount.second += 1;

  return joltsCount.first * joltsCount.second;
};
