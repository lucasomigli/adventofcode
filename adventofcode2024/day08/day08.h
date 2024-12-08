#ifndef DAY08_H
#define DAY08_H

#include "../utils2024.h"

struct Point {
    int x, y;
    char c = '.';
    Point(int _x, int _y) : x(_x), y(_y) {};
    Point(int _x, int _y, char _c) : x(_x), y(_y), c(_c) {};
    bool operator==(const Point& right) const { return (x == right.x) && (y == right.y); }
    bool operator<(const Point& right) const {
        if (x == right.x) {
            return y < right.y;
        }
        return x < right.x;
    }
};

std::vector<Point> getAllPairs(const std::vector<Point>& points, const std::pair<int, int>& _gridSize) {
    std::vector<Point> antinodes;
    for (size_t i = 0; i < points.size(); ++i) {
        int dx, dy;
        for (size_t j = i + 1; j < points.size(); ++j) {
            std::cout << "Pair: (" << points[i].x << ", " << points[i].y << ") and (" << points[j].x << ", " << points[j].y << ")" << std::endl;  // debug
            dx = points[i].x - points[j].x;
            dy = points[i].y - points[j].y;
            std::vector<Point> nodes = {Point(points[i].x + dx, points[i].y + dy), Point(points[j].x - dx, points[j].y - dy)};

            // filter based on the antinodes being withn map bounds
            for (auto& el : nodes) {
                if (el.x >= 0 && el.x <= _gridSize.first && el.y >= 0 && el.y <= _gridSize.second) {
                    std::cout << "Antinode: (" << el.x << ", " << el.y << ")" << std::endl;  // debug
                    antinodes.push_back(el);
                }
            }
        }
    }
    return antinodes;
}

inline long Solver::Solve_Day08_part1() {
    std::string line;
    std::map<std::pair<int, int>, Point> grid;
    std::pair<int, int> gridSize;
    std::map<char, std::vector<Point>> antennas;

    // build grid
    int row = 0, cols = 0;
    while (std::getline(file, line)) {
        cols = line.size();
        for (int col = 0; col < cols; ++col) {
            char* c = &line[col];
            Point* point = new Point(col, row, *c);
            grid.emplace(std::make_pair(col, row), *point);

            // note the antennas position and store them
            if (*c != '.') {
                antennas[*c].push_back(*point);
            }
        }
        ++row;
    }

    // set gridSize bounds
    gridSize = {cols, row};

    // build antinodes
    std::vector<Point> antinodes;
    for (auto it = antennas.begin(); it != antennas.end(); it++) {
        for (auto& el : getAllPairs(it->second, gridSize)) {
            antinodes.push_back(el);
        }
    }

    std::set<Point> filtered(antinodes.begin(), antinodes.end());

    return filtered.size();
}

#endif  // DAY08_H