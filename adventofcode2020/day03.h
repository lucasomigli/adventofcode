#ifndef DAY03_2020_H
#define DAY03_2020_H

#ifndef UTILS_H
#include "utils2020.h"
#endif

inline int traverseTrees(const std::string &fileName,
                         const std::pair<int, int> &t) {
  std::fstream file;
  file.open(fileName);

  std::string s;
  file >> s;

  char c = 0;
  int move = std::get<0>(t);
  int currentPosition = 0;
  int countTrees = 0;
  int lengthLine = s.size();

  while (!file.eof() && !s.empty()) {
    if (c == '#') {
      countTrees += 1;
    }
    for (int i = 0; i < std::get<1>(t); i++) {
      file >> s;
    }

    int newPos = (currentPosition + move) % lengthLine;
    c = s[newPos];
    currentPosition = newPos;
  }

  return countTrees;
}

inline int traverseMultipleTrees() {
  std::array<std::pair<int, int>, 5> slopes = {
    std::make_pair(1, 1), std::make_pair(3, 1), std::make_pair(5, 1),
    std::make_pair(7, 1), std::make_pair(1, 2)
  };
  int slopes_size = sizeof(slopes) / sizeof(slopes[0]);
  long res = 1;
  for (int i = 0; i < slopes_size; i++) {
    int r = traverseTrees("input.txt", slopes[i]);
    std::cout << r << std::endl;
    res *= r;
    std::cout << res << std::endl;
  }

  return res;
}

#endif
