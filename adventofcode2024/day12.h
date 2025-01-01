#ifndef DAY12_H
#define DAY12_H

#include "utils2024.h"

using Point = utils::Point;

long Solver::Solve_Day12_part1() {
    std::string line;
    std::map<std::pair<int, int>, Point> grid;
    std::pair<int, int> gridSize;
    std::map<char, std::vector<Point>> antennas;

    // build grid
    int row = 0, cols = 0;
    while (std::getline(file, line)) {
        cols = line.size();
        Point* point;
        for (int col = 0; col < cols; ++col) {
            char* c = &line[col];
            point = new Point(col, row, *c);
            grid.emplace(std::make_pair(col, row), *point);

            // note the antennas position and store them
            if (*c != '.') {
                antennas[*c].push_back(*point);
            }
        }
        delete point;
        ++row;
    }

    // set gridSize bounds
    gridSize = {cols, row};

    PrintGrid(grid, gridSize);  // Print grid for debug

    return 0;
}

#endif
