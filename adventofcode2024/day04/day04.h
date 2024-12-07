#ifndef DAY04_H
#define DAY04_H

#include <array>

#include "../utils2024.h"

struct Coordinate {
    int x;
    int y;
    char letter;

    Coordinate() : x(0), y(0), letter('0') {
    }

    Coordinate(int _x, int _y, char _c) : x(_x), y(_y), letter(_c) {
    }
};

inline bool searchDirection(const Coordinate &point, const std::pair<int, int> &direction,
                            const std::pair<int, int> &bounds,
                            const std::map<std::pair<int, int>, Coordinate> &M) {
    const std::string target = "XMAS";
    int x = point.x, y = point.y;

    for (char c : target) {
        if (x < 0 || y < 0 || x >= bounds.first || y >= bounds.second || M.at({x, y}).letter != c) {
            return false;
        }
        x += direction.first;
        y += direction.second;
    }
    return true;
}

inline int Solver::Solve_Day04_part1() {
    std::string line;
    std::map<std::pair<int, int>, Coordinate> M;
    int result = 0;

    // Build grid
    int rows = 0, cols = 0;
    while (std::getline(file, line)) {
        cols = line.size();
        for (int col = 0; col < cols; ++col) {
            M[{rows, col}] = Coordinate(rows, col, line[col]);
        }
        ++rows;
    }

    const std::array<std::pair<int, int>, 8> directions = {
        {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}}};

    // Search starting from 'X'
    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            if (M[{x, y}].letter == 'X') {
                for (const auto &direction : directions) {
                    result += (searchDirection(M[{x, y}], direction, {rows, cols}, M));
                }
            }
        }
    }

    return result;
}

/*--------------
------part 2----
--------------*/

inline bool searchDirectionX(const Coordinate &point, const std::pair<int, int> &bounds,
                             const std::map<std::pair<int, int>, Coordinate> &M) {
    const int target = 'M' + 'S';
    int x = point.x, y = point.y;

    // return false if out of bounds
    if (x - 1 < 0 || y - 1 < 0 || x + 1 >= bounds.first || y + 1 >= bounds.second) {
        return false;
    }

    // check if letters at the edges around the centre are valid
    bool check1 = M.at({x - 1, y - 1}).letter + M.at({x + 1, y + 1}).letter == target;
    bool check2 = M.at({x - 1, y + 1}).letter + M.at({x + 1, y - 1}).letter == target;

    return check1 && check2;
}

inline int Solver::Solve_Day04_part2() {
    std::string line;
    std::map<std::pair<int, int>, Coordinate> M;
    int result = 0;

    // Build grid
    int rows = 0, cols = 0;
    while (std::getline(file, line)) {
        cols = line.size();
        for (int col = 0; col < cols; ++col) {
            M[{rows, col}] = Coordinate(rows, col, line[col]);
        }
        ++rows;
    }

    // Search starting from 'A'
    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            if (M[{x, y}].letter == 'A') {
                result += (searchDirectionX(M[{x, y}], {rows, cols}, M));
            }
        }
    }

    return result;
}

#endif  // DAY04_H
