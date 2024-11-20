#ifndef DAY13_H
#define DAY13_H

#ifndef UTILS_H
#include "../utils.h"
#endif

int Solver::Solve_day_13_part1() {
  std::string line;
  int earliestTime;
  int earliestBus;
  int minimumBusWait = 10000;
  std::vector<int> buses;

  // Get earliest time
  std::getline(file, line);
  earliestTime = std::stoi(line);

  // Get list of buses into memory
  while (std::getline(file, line, ',')) {
    if (line == "x") continue;
    buses.push_back(std::stoi(line));
  }

  int counter = 1;
  for (size_t i = 0; i < buses.size(); ++i) {
    counter = 1;
    int tmp = 0;
    while (tmp <= earliestTime) {
      tmp = buses[i] * counter;
      ++counter;
    }

    if ((tmp - earliestTime) < minimumBusWait) {
      minimumBusWait = tmp - earliestTime;
      earliestBus = buses[i];
    }
  }

  return minimumBusWait * earliestBus;
}

int Solver::Solve_day_13_part2() {
  std::string line;
  long highestBusId = 0;
  int highestBusId_t;
  std::vector<long> buses;

  // Get earliest time
  std::getline(file, line);

  // Get list of buses into memory
  int pos_t = 0;
  while (std::getline(file, line, ',')) {
    if (line == "x") {
      buses.push_back(0);
    } else {
      long busId = std::stol(line);
      buses.push_back(busId);
      if (highestBusId < busId) {
        highestBusId = busId;
        highestBusId_t = pos_t;
      }
    }
    ++pos_t;
  }

  if (highestBusId != buses[highestBusId_t]) {
    return -1;
  }

  int i = 1;
  long relativeTime = 0;
  bool inLine = false;
  while (!inLine) {
    highestBusId = i * buses[highestBusId_t];
    for (size_t t = 0; t < buses.size(); ++t) {
      if (buses[t] == 0) continue;
      relativeTime = highestBusId + (t - highestBusId_t);
      if (relativeTime % buses[t] != 0) {
        inLine = false;
        break;
      } else {
        inLine = true;
      }
    }
    ++i;
  }

  return highestBusId - highestBusId_t;
}

#endif
