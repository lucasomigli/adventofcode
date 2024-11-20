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
  std::getline(file, line);  // Skip the earliest timestamp (not used in Part 2)

  std::vector<std::pair<int, long>> buses;
  int pos_t = 0;

  // Parse bus IDs with offsets
  while (std::getline(file, line, ',')) {
    if (line != "x") {
      unsigned long busId = std::stol(line);
      buses.emplace_back(pos_t, busId);
    }
    ++pos_t;
  }

  // Initialize time and step size
  unsigned long timestamp = 0;
  unsigned long step = buses[0].second;

  // Iterate over each bus and offset
  for (size_t i = 1; i < buses.size(); ++i) {
    int offset = buses[i].first;
    unsigned long busId = buses[i].second;

    // Increase timestamp until it satisfies the current bus's offset condition
    while ((timestamp + offset) % busId != 0) {
      timestamp += step;
    }

    // Multiply step by busId to keep aligned with all previous buses
    step *= busId;
  }
  std::cout << timestamp << std::endl;
  return timestamp;
}

#endif
