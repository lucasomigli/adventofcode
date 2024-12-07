#ifndef DAY06_H
#define DAY06_H

#include "../utils2024.h"

struct Coordinate {
    int x;
    int y;
    bool isObstacle;

    Coordinate() : x(0), y(0), isObstacle(false) {}

    Coordinate(int _x, int _y, bool _isObstacle) : x(_x), y(_y), isObstacle(_isObstacle) {}

    Coordinate(int _x, int _y, char _c) : x(_x), y(_y), isObstacle(_c == '#' ? isObstacle = true : isObstacle = false) {}
};

struct GuardPosition : public Coordinate {
    char direction;

    GuardPosition() {}
    GuardPosition(char c) : direction(c) {}
    GuardPosition(int _x, int _y, char _c) {
        x = _x;
        y = _y;
        direction = _c;
    }
};

inline long Solver::Solve_Day06_part1() {
    std::string line;
    std::map<std::pair<int, int>, Coordinate> grid;
    std::set<std::pair<int, int>> visitedPositions;
    GuardPosition guardPosition;

    // Build grid
    int row = 0, cols = 0;
    while (std::getline(file, line)) {
        cols = line.size();
        for (int col = 0; col < cols; ++col) {
            grid[{col, row}] = Coordinate(col, row, line[col]);
            if (line[col] != '.' && line[col] != '#') {
                guardPosition = GuardPosition(col, row, line[col]);
            }
        }
        ++row;
    }

    std::cout << cols << " " << row << std::endl;
    std::cout << "DEBUG " << guardPosition.x << " " << guardPosition.y << " " << std::endl;
    // for (int i = 0; i < 10; i++) {
    //     std::cout << "DEBUGGED " << grid[{i, 1}].isObstacle << std::endl;
    //     std::cout << grid[{i, 1}].x << " " << grid[{i, 1}].y << std::endl;
    // }

    std::map<char, std::pair<int, int>> directions = {{'^', {0, -1}}, {'>', {1, 0}}, {'v', {0, 1}}, {'<', {-1, 0}}};
    std::map<char, char> nextDirection = {{'^', '>'}, {'>', 'v'}, {'v', '<'}, {'<', '^'}};

    while (guardPosition.x >= 0 && guardPosition.x < cols && guardPosition.y >= 0 && guardPosition.y < row) {
        auto [dx, dy] = directions[guardPosition.direction];
        int nextX = guardPosition.x + dx;
        int nextY = guardPosition.y + dy;

        if (grid.find({nextX, nextY}) != grid.end()) {
            if (!grid[{nextX, nextY}].isObstacle) {
                guardPosition.x = nextX;
                guardPosition.y = nextY;
            } else {
                guardPosition.direction = nextDirection[guardPosition.direction];
                continue;
            }
        } else {
            break;
        }

        visitedPositions.insert(std::make_pair(guardPosition.x, guardPosition.y));
    }

    return visitedPositions.size();
}

#endif  // DAY06_H