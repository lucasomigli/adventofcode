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
                if (el.x >= 0 && el.x < _gridSize.first && el.y >= 0 && el.y < _gridSize.second) {
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

bool isWithinBounds(Point p, const std::pair<int, int>& bounds) {
    if (p.x >= 0 && p.x < bounds.first && p.y >= 0 && p.y < bounds.second) {
        return true;
    }
    return false;
}

std::vector<Point> getAllPairsPart2(const std::vector<Point>& points, const std::pair<int, int>& _gridSize) {
    if (points.size() < 2) {
        return std::vector<Point>{};  // return empty if no pairs of antennas
    }

    std::vector<Point> antinodes;
    for (size_t i = 0; i < points.size(); ++i) {
        int dx, dy;
        for (size_t j = i + 1; j < points.size(); ++j) {
            std::cout << "Pair: (" << points[i].x << ", " << points[i].y << ") and (" << points[j].x << ", " << points[j].y << ")" << std::endl;  // debug

            // build nodes until out dx and dy are out of bounds
            dx = points[i].x - points[j].x;
            dy = points[i].y - points[j].y;

            Point initial = points[i];
            std::vector<Point> nodes = {initial};
            for (auto sign : {1, -1}) {
                int _m = 1;
                Point newPoint = initial;
                while (isWithinBounds(newPoint, _gridSize)) {
                    nodes.push_back(newPoint);
                    newPoint = Point(initial.x + dx * sign * _m, initial.y + dy * sign * _m);
                    ++_m;
                }
            }

            // filter based on the antinodes being withn map bounds
            for (auto& el : nodes) {
                if (isWithinBounds(el, _gridSize)) {
                    std::cout << "Antinode: (" << el.x << ", " << el.y << ")" << std::endl;  // debug
                    antinodes.push_back(el);
                }
            }
        }
    }
    return antinodes;
}

inline long Solver::Solve_Day08_part2() {
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
        for (auto& el : getAllPairsPart2(it->second, gridSize)) {
            antinodes.push_back(el);
        }
    }

    std::set<Point> filtered(antinodes.begin(), antinodes.end());

    return filtered.size();
}

#endif  // DAY08_H