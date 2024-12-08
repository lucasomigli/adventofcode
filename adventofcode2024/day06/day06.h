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

    // build grid
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

inline bool moveGuard(GuardPosition& _guardPosition,
                      std::map<std::pair<int, int>, Coordinate>& _grid,
                      const std::pair<int, int>& _gridSize,
                      std::set<std::tuple<int, int, char>>& _visitedPositions,
                      bool firstRun = false) {
    std::map<char, std::pair<int, int>> directions = {{'^', {0, -1}}, {'>', {1, 0}}, {'v', {0, 1}}, {'<', {-1, 0}}};
    std::map<char, char> nextDirection = {{'^', '>'}, {'>', 'v'}, {'v', '<'}, {'<', '^'}};

    // move guard on the grid, noting the visitedPositions and direction
    int cols = _gridSize.first, row = _gridSize.second;
    while (_guardPosition.x >= 0 && _guardPosition.x < cols && _guardPosition.y >= 0 && _guardPosition.y < row) {
        auto [dx, dy] = directions[_guardPosition.direction];
        int nextX = _guardPosition.x + dx;
        int nextY = _guardPosition.y + dy;

        if (_grid.find({nextX, nextY}) != _grid.end()) {
            if (!_grid[{nextX, nextY}].isObstacle) {
                _guardPosition.x = nextX;
                _guardPosition.y = nextY;
            } else {
                _guardPosition.direction = nextDirection[_guardPosition.direction];
                continue;
            }
        } else {
            break;
        }

        // check if position has been visited already with the same direction
        std::tuple<int, int, char> currentPos = {_guardPosition.x, _guardPosition.y, _guardPosition.direction};
        if (_visitedPositions.find(currentPos) != _visitedPositions.end()) {
            return false;
        }

        // build visited positions for the first time only
        if (firstRun) {
            _visitedPositions.insert({_guardPosition.x, _guardPosition.y, _guardPosition.direction});
        }
    }

    return true;
}

inline long Solver::Solve_Day06_part2() {
    std::string line;
    std::map<std::pair<int, int>, Coordinate> grid;
    std::set<std::tuple<int, int, char>> visitedPositions;
    GuardPosition guardPosition;
    GuardPosition cp_guardPosition;
    long solution = 0;

    // build grid
    int row = 0, cols = 0;
    while (std::getline(file, line)) {
        cols = line.size();
        for (int col = 0; col < cols; ++col) {
            grid[{col, row}] = Coordinate(col, row, line[col]);
            if (line[col] != '.' && line[col] != '#') {
                guardPosition = GuardPosition(col, row, line[col]);
                cp_guardPosition = guardPosition;  // copy of the original guard position
            }
        }
        ++row;
    }

    std::pair<int, int> gridSize(cols, row);
    moveGuard(guardPosition, grid, gridSize, visitedPositions, true);

    // remove original guardposition from list of obstacles
    guardPosition = cp_guardPosition;
    std::set<std::tuple<int, int, char>> toRemove;
    std::for_each(visitedPositions.begin(), visitedPositions.end(),
                  [&toRemove, guardPosition](const std::tuple<int, int, char>& tpl) {
                      if (std::get<1>(tpl) >= guardPosition.y || std::get<0>(tpl) == guardPosition.y) {
                          toRemove.insert(tpl);
                      }
                  });
    for (const auto& element : toRemove) {
        visitedPositions.erase(element);
    }

    // iterate through modified grid to find infinite loops
    for (const std::tuple<int, int, char>& tpl : visitedPositions) {
        // change the value of a single position to being an obstacle
        std::map<std::pair<int, int>, Coordinate> cp_grid = grid;
        int x = std::get<0>(tpl), y = std::get<1>(tpl);
        cp_grid[std::make_pair(x, y)].isObstacle = true;

        std::cout << "DEBUG: " << cp_grid[std::make_pair(x, y)].isObstacle << " " << cp_grid[std::make_pair(x, y)].x << " " << cp_grid[std::make_pair(x, y)].y << std::endl;
        std::cout << "DEBUG: " << grid[std::make_pair(x, y)].isObstacle << " " << grid[std::make_pair(x, y)].x << " " << grid[std::make_pair(x, y)].y << std::endl;

        // run through moving the guard again to see if it loop infinitely
        // reset guard position to original
        guardPosition = cp_guardPosition;
        bool isValid = moveGuard(guardPosition, cp_grid, gridSize, visitedPositions);
        if (!isValid) {
            solution++;
        }

        // prepare the cp_grid to be the same as the original again
        cp_grid = grid;
    }

    return solution;
}

#endif  // DAY06_H