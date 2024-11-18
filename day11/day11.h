#ifndef DAY11_DAY11_H_
#define DAY11_DAY11_H_

#ifndef UTILS_H
#include "../utils.h"
#endif

int Solver::Solve_day_11_part1() {
  std::cout << "Day 11 of adventofcode" << std::endl;
  std::string line;
  std::map<std::pair<int, int>, char> M;
  int M_x_size = 0;
  int M_y_size = 0;
  int occupiedSeats = 0;

  // Insert seats into the M matrix.
  int row = -1;
  while (std::getline(file, line)) {
    row += 1;
    size_t c;
    for (c = 0; c < line.size(); c++) {
      M.insert({{row, c}, line[c]});
      if (line[c] == '#') {
        occupiedSeats += 1;
      }
    }
    M_x_size = c;
  }
  M_y_size = row + 1;

  // Transform seats depending on location and adjecent seats.
  bool swapped = true;
  while (swapped == true) {
    std::map<std::pair<int, int>, char> M_copy = M;
    int adjacentSeats = 0;
    swapped = false;
    for (int i = 0; i < M_y_size; ++i) {
      for (int j = 0; j < M_x_size; ++j) {
        std::cout << i << " " << j << M[{i, j}] << "\n";
        if (M_copy[{i, j}] == 'L' && M_copy[{i - 1, j - 1}] != '#' &&
            M_copy[{i - 1, j + 1}] != '#' && M_copy[{i, j - 1}] != '#' &&
            M_copy[{i, j + 1}] != '#' && M_copy[{i + 1, j - 1}] != '#' &&
            M_copy[{i + 1, j + 1}] != '#') {
          M[{i, j}] = '#';
          occupiedSeats += 1;
          swapped = true;
        } else if (M_copy[{i, j}] == 'L') {
          if (M_copy[{i - 1, j - 1}] == '#') {
            adjacentSeats += 1;
          }
          if (M_copy[{i - 1, j + 1}] == '#') {
            adjacentSeats += 1;
          }
          if (M_copy[{i, j - 1}] == '#') {
            adjacentSeats += 1;
          }
          if (M_copy[{i, j + 1}] == '#') {
            adjacentSeats += 1;
          }
          if (M_copy[{i + 1, j - 1}] == '#') {
            adjacentSeats += 1;
          }
          if (M_copy[{i + 1, j + 1}] == '#') {
            adjacentSeats += 1;
          }

          if (adjacentSeats >= 4) {
            M[{i, j}] = 'L';
            occupiedSeats -= 1;
            swapped = true;
          }
          adjacentSeats = 0;
        }
      }
    }
  }

  return occupiedSeats;
};

#endif
