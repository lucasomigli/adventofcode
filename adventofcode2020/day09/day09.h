#ifndef DAY09_2020_H
#define DAY09_2020_H

#ifndef UTILS_2020_H
#include "../utils2020.h"
#endif

long Solver::Solve_day_9_part2() {
  std::cout << "Starting with day 9 solution part 2..." << std::endl;

  std::string line;
  long targetSum =
      1398413738; // The target sum to find in the contiguous subarray
  std::vector<long> memory;

  // Load values into memory from file
  while (std::getline(file, line)) {
    long currentValue = std::stol(line);
    memory.push_back(currentValue);
  }

  // Sliding window approach to find the contiguous subarray with target sum
  long currentSum = 0;
  size_t start = 0;

  for (size_t end = 0; end < memory.size(); ++end) {
    std::cout << currentSum << " " << start << std::endl;
    currentSum += memory[end];

    // Shrink window from the left if currentSum exceeds targetSum
    while (currentSum > targetSum && start < end) {
      currentSum -= memory[start];
      ++start;
    }

    // Check if we have found the target sum
    if (currentSum == targetSum) {
      auto minmax =
          std::minmax_element(memory.begin() + start, memory.begin() + end + 1);
      return *minmax.first + *minmax.second;
    }
  }

  return 0; // Return 0 if no such subarray is found
}

long Solver::Solve_day_9_part1() {
  std::cout << "Starting with day 9 solution..." << std::endl;

  std::string line;
  int limit = 25;
  long currentValue = 0;
  int position = 0;
  std::vector<long> queueStack;

  while (std::getline(file, line)) {
    // Sets current value to an integer and populate the beginnin stack
    currentValue = std::stol(line);
    if (position < limit) {
      queueStack.push_back(currentValue);
      ++position;
      continue;
    }

    // Search for the value existing in the queueStack
    long valueToSearch;
    std::vector<long>::iterator it;
    int count = 0;
    for (it = queueStack.begin(); it != queueStack.end(); it++) {
      valueToSearch = currentValue - *it;
      auto isExisting =
          std::find(queueStack.begin(), queueStack.end(), valueToSearch);

      if (isExisting != std::end(queueStack) && isExisting != it) {
        break;
      }
      count++;
    }

    if (count >= limit) {
      return currentValue;
    }

    // Erase first item in and push current value into the stack
    queueStack.erase(queueStack.begin());
    queueStack.push_back(currentValue);
    ++position;
  }

  return 0;
}

#endif
