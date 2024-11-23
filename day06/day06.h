#ifndef UTILS_H
#include "utils.h"
#endif

class Day_6_Solver : Solver {
private:
public:
  Day_6_Solver(const std::string &_fileInput) : Solver(_fileInput) {
  }

  int findSolution() {
    long finalCount = 0;
    int groupCount = 0;
    std::string line;
    std::set<char> storage;
    std::set<char> tmpStorage;
    std::vector<int> tmp;
    bool isFirstLine = true;

    while (std::getline(this->file, line)) {
      if (line.size() < 1) {
        groupCount = storage.size();
        finalCount += groupCount;
        storage.clear();
        isFirstLine = true;
        std::cout << "Group Count: " << groupCount << std::endl;
        continue;
      } else {
        std::cout << line << std::endl;
        for (char c: line) {
          if (!isFirstLine) {
            tmpStorage.insert(c);
            continue;
          }
          storage.insert(c);
        }

        if (!isFirstLine) {
          tmp = {};
          std::set_intersection(storage.begin(), storage.end(),
                                tmpStorage.begin(), tmpStorage.end(),
                                std::back_inserter(tmp));
          storage.clear();
          tmpStorage.clear();
          for (int i: tmp) {
            storage.insert(i);
          }
        }

        if (isFirstLine) {
          isFirstLine = false;
        }
      }
    }
    finalCount += storage.size();
    return finalCount;
  }
};
