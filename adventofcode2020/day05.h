#ifndef DAY05_2020_H
#define DAY05_2020_H

#ifndef UTILS_H
#include "utils2020.h"
#endif

inline long findAirplaneSeats(const std::string &inputFile) {
  std::fstream file;
  file.open(inputFile);
  std::string line;
  int rowUpper = 128;
  int rowLower = 0;
  int columnRight = 8;
  int columnLeft = 0;
  long seatId;
  long maxSeatId = 0;

  while (std::getline(file, line)) {
    std::cout << line << std::endl;

    // Initialize variables.
    rowUpper = 128;
    rowLower = 0;
    columnRight = 8;
    columnLeft = 0;

    for (char c: line) {
      // Work through the row number.
      if (c == 'F') {
        rowUpper = rowUpper - ((rowUpper - rowLower) / 2);
      } else if (c == 'B') {
        rowLower = rowUpper - ((rowUpper - rowLower) / 2);
      } else if (c == 'R') {
        columnLeft = columnRight - ((columnRight - columnLeft) / 2);
      } else if (c == 'L') {
        columnRight = columnRight - ((columnRight - columnLeft) / 2);
      }
    }
    seatId = rowLower * 8 + columnLeft;
    maxSeatId = std::max(seatId, maxSeatId);
  }

  return maxSeatId;
}

#endif
