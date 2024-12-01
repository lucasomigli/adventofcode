#ifndef DAY01_2020_H
#define DAY01_2020_H

#ifndef UTILS_H
#include "../utils2020.h"
#endif

inline std::array<int, 3> findNumbersFromFile(const std::string &fileName) {
  std::fstream file;
  file.open(fileName);
  std::string line;
  std::vector<int> container;

  file >> line;
  container.push_back(std::stoi(line));
  file >> line;

  while (!file.eof() && !line.empty()) {
    int i = std::stoi(line);

    // Check for pairs in the container that sum with `i` to 2020
    for (int j: container) {
      int k = 2020 - j - i;

      auto iter = std::find(container.begin(), container.end(), k);
      if (iter !=
          container.end()) // Ensure `iter` is valid before dereferencing
      {
        std::cout << "Found values: " << i << ", " << j << ", " << k
            << std::endl;
        long multiplierResult = i * j * k;
        std::cout << "The solution is: " + std::to_string(multiplierResult)
            << std::endl;
        return {i, j, k};
      }
    }

    // Add the current value to the container for future checks
    file >> line;
    container.push_back(i);
  }
  file.close();
  std::array<int, 3> noFind = {0, 0, 0};
  return noFind;
}

#endif
