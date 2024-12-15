#ifndef DAY11_2020_H
#define DAY11_2020_H

#ifndef UTILS_2020_H
#include "utils2020.h"
#endif

void helper(std::map<std::pair<int, int>, char> &m, size_t m_size_x,
            size_t m_size_y) {
  std::cout << "-----------------" << std::endl;
  for (size_t i = 0; i < m_size_y; ++i) {
    std::stringstream ss;
    for (size_t j = 0; j < m_size_x; ++j) {
      ss << m[{i, j}];
    }
    std::cout << ss.str() << std::endl;
    ss.clear();
  }
}

void helper(std::vector<std::vector<char> > &m, size_t m_size_x,
            size_t m_size_y) {
  std::cout << "-----------------" << std::endl;
  for (size_t i = 0; i < m_size_y; ++i) {
    std::stringstream ss;
    for (size_t j = 0; j < m_size_x; ++j) {
      ss << m[i][j];
    }
    std::cout << ss.str() << std::endl;
    ss.clear();
  }
}

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
      M[{row, c}] = line[c];
      if (line[c] == '#') {
        occupiedSeats += 1;
      }
    }
    M_x_size = c;
  }
  M_y_size = row + 1;

  // Transform seats depending on location and adjecent seats.
  bool swapped = true;
  helper(M, M_x_size, M_y_size);
  while (swapped == true) {
    std::map<std::pair<int, int>, char> M_copy = M;
    int adjacentSeats = 0;
    swapped = false;
    for (int i = 0; i < M_y_size; ++i) {
      for (int j = 0; j < M_x_size; ++j) {
        if (M_copy[{i, j}] == 'L' && M_copy[{i - 1, j - 1}] != '#' &&
            M_copy[{i - 1, j}] != '#' && M_copy[{i - 1, j + 1}] != '#' &&
            M_copy[{i, j - 1}] != '#' && M_copy[{i, j + 1}] != '#' &&
            M_copy[{i + 1, j - 1}] != '#' && M_copy[{i + 1, j}] != '#' &&
            M_copy[{i + 1, j + 1}] != '#') {
          M[{i, j}] = '#';
          occupiedSeats += 1;
          swapped = true;
        } else if (M_copy[{i, j}] == '#') {
          // Search for all possible combinations around the seats
          if (M_copy[{i - 1, j - 1}] == '#') {
            adjacentSeats += 1;
          }
          if (M_copy[{i - 1, j}] == '#') {
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
          if (M_copy[{i + 1, j}] == '#') {
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
    helper(M, M_x_size, M_y_size);
  }

  return occupiedSeats;
};

char searchDirection(const std::vector<std::vector<char> > &m,
                     std::pair<int, int> m_size, std::pair<int, int> initPos,
                     const std::pair<int, int> to) {
  int newX = initPos.first;
  int newY = initPos.second;
  char initial = m[initPos.second][initPos.first];

  if (initial == '.') {
    return initial;
  }

  bool inBounds = true;

  // Iterate through while within bounds only
  while (inBounds) {
    newX += to.first;
    newY += to.second;
    inBounds =
        newY >= 0 && newY < m_size.second && newX >= 0 && newX < m_size.first;
    if (inBounds) {
      if (m[newY][newX] == '.') {
        continue;
      } else if (initial == 'L' && m[newY][newX] == 'L') {
        return 'L';
      }
      return m[newY][newX];
    } else if (initial == 'L' && !inBounds) {
      return 'L';
    }

    return '.';
  }

  return '.';
}

std::map<char, int> searchAllDirections(const std::vector<std::vector<char> > &m,
                                        const std::pair<int, int> &m_size,
                                        const std::pair<int, int> &initPos) {
  char currentFind;
  std::map<char, int> countSeats;
  for (int x = -1; x <= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      // Ignore when no direction is given
      if (x == y && y == 0) {
        continue;
      }

      currentFind = searchDirection(m, m_size, initPos, {x, y});
      countSeats[currentFind] += 1;
    }
  }
  return countSeats;
}

int Solver::Solve_day_11_part2() {
  std::cout << "Day 11 of adventofcode" << std::endl;
  std::string line;
  std::vector<std::vector<char> > M;
  int M_x_size = 0;
  int M_y_size = 0;
  int occupiedSeats = 0;

  // Insert seats into the M matrix.
  while (std::getline(file, line)) {
    std::vector<char> rowVec(line.begin(), line.end());
    M.push_back(rowVec);
    M_x_size = line.size();
    for (char c: rowVec) {
      if (c == '#') {
        occupiedSeats += 1;
      }
    }
  }
  M_y_size = M.size();

  // Transform seats depending on location and adjacent seats.
  bool swapped = true;
  int transformations = 0;

  while (swapped) {
    std::cout << "DEBUG: transforming..." << transformations << std::endl;
    std::vector<std::vector<char> > M_copy = M;
    swapped = false;

    for (int y = 0; y < M_y_size; ++y) {
      for (int x = 0; x < M_x_size; ++x) {
        std::map<char, int> tmpCount =
            searchAllDirections(M_copy, {M_x_size, M_y_size}, {x, y});

        if (M_copy[y][x] == 'L' && tmpCount['L'] >= 8) {
          // Search when seat L is empty
          M[y][x] = '#';
          occupiedSeats += 1;
          swapped = true;
        } else if (M_copy[y][x] == '#' && tmpCount['#'] >= 5) {
          M[y][x] = 'L';
          occupiedSeats -= 1;
          swapped = true;
        }
      }
    }

    transformations += 1;
  }

  return occupiedSeats;
}

#endif
