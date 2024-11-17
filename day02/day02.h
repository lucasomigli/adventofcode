#ifndef UTILS_H
#include "utils.h"
#endif

inline int findValidPasswords(const std::string &fileName) {
  std::fstream file;
  file.open(fileName);

  int count = 0;
  std::string s;
  file >> s;

  while (!file.eof() && !s.empty()) {
    std::vector<int> positions;
    char c;
    int array[3] = {0, 1, 2};
    for (auto i : array) {
      if (s.empty()) {
        break;
      }

      std::string segment;
      std::stringstream ss(s);
      switch (i) {
        case 0:
          while (std::getline(ss, segment, '-')) {
            positions.push_back(std::stoi(segment) - 1);
          }
          break;

        case 1:
          c = s[0];
          break;

        case 2:
          int co = 0;
          for (auto el : positions) {
            if (c == s[el]) {
              co++;
            }
          }

          if (co == 1) {
            count++;
          }

          break;
      }

      file >> s;
    };
  }

  file.close();
  return count;
}
