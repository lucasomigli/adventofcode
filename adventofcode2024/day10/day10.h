#ifndef DAY10_H
#define DAY10_H

#include "../utils2024.h"

struct Point {
    int x, y;
    int value = -1;
    Point(int _x, int _y) : x(_x), y(_y) {};
    Point(int _x, int _y, char _c) : x(_x), y(_y) {
        std::string toString = std::to_string(_c - '0');
        value = std::stoi(toString);
    };
    bool operator==(const Point& right) const { return (x == right.x) && (y == right.y); }
    bool operator<(const Point& right) const {
        if (x == right.x) {
            return y < right.y;
        }
        return x < right.x;
    }
};

inline void findTrailHead(Point* ptrPoint, std::map<std::pair<int, int>, Point>& _grid, std::set<Point>& _endpoints, int& _trailHeadsSum) {
    int x = ptrPoint->x;
    int y = ptrPoint->y;

    std::vector<std::pair<int, int>> _directions = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    for (const auto& dir : _directions) {
        int newX = x + dir.first;
        int newY = y + dir.second;
        auto it = _grid.find({newX, newY});
        if (it != _grid.end()) {
            Point* newPoint = &it->second;
            if (newPoint->value == ptrPoint->value + 1) {
                findTrailHead(newPoint, _grid, _endpoints, _trailHeadsSum);
            }
        }
    }

    // if the current point is the end of a trail (value 9), count it as a good trail
    auto it = _endpoints.find(*ptrPoint);
    if (ptrPoint->value == 9 && it == _endpoints.end()) {
        _trailHeadsSum++;
        _endpoints.insert(*ptrPoint);
    }
}

inline long Solver::Solve_Day10_part1() {
    std::string line;
    std::map<std::pair<int, int>, Point> grid;
    std::pair<int, int> gridSize = {0, 0};
    std::vector<Point*> startingPoints;

    // build grid
    while (std::getline(file, line)) {
        gridSize.second = line.size();
        for (int col = 0; col < gridSize.second; ++col) {
            char* c = &line[col];
            Point* point = new Point(col, gridSize.first, *c);
            grid.emplace(std::make_pair(col, gridSize.first), *point);

            // note the starting points
            if (*c == '0') {
                startingPoints.push_back(point);
            }
        }
        ++gridSize.first;
    }

    static int trailHeadsSum = 0;
    std::set<Point> endPoints;
    for (auto point : startingPoints) {
        findTrailHead(point, grid, endPoints, trailHeadsSum);
        endPoints.clear();
    }

    return trailHeadsSum;
}

inline void findTrailHeadPart2(Point* ptrPoint, std::map<std::pair<int, int>, Point>& _grid, int& _trailHeadsSum) {
    int x = ptrPoint->x;
    int y = ptrPoint->y;

    std::vector<std::pair<int, int>> _directions = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    for (const auto& dir : _directions) {
        int newX = x + dir.first;
        int newY = y + dir.second;
        auto it = _grid.find({newX, newY});
        if (it != _grid.end()) {
            Point* newPoint = &it->second;
            if (newPoint->value == ptrPoint->value + 1) {
                findTrailHeadPart2(newPoint, _grid, _trailHeadsSum);
            }
        }
    }

    // if the current point is the end of a trail (value 9), count it as a good trail
    if (ptrPoint->value == 9) {
        _trailHeadsSum++;
    }
}

inline long Solver::Solve_Day10_part2() {
    std::string line;
    std::map<std::pair<int, int>, Point> grid;
    std::pair<int, int> gridSize = {0, 0};
    std::vector<Point*> startingPoints;

    // build grid
    while (std::getline(file, line)) {
        gridSize.second = line.size();
        for (int col = 0; col < gridSize.second; ++col) {
            char* c = &line[col];
            Point* point = new Point(col, gridSize.first, *c);
            grid.emplace(std::make_pair(col, gridSize.first), *point);

            // note the starting points
            if (*c == '0') {
                startingPoints.push_back(point);
            }
        }
        ++gridSize.first;
    }

    static int trailHeadsSum = 0;
    for (auto point : startingPoints) {
        findTrailHeadPart2(point, grid, trailHeadsSum);
    }

    return trailHeadsSum;
}

#endif