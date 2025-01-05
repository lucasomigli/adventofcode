#ifndef DAY15_H
#define DAY15_H

#include "utils2024.h"

struct PlayField {
    const int size = 50;
    char grid[50][50];
    std::pair<int, int> robotPosition = {0, 0};

    PlayField() {
        for (size_t y = 0; y < size; ++y) {
            for (size_t x = 0; x < size; ++x) {
                grid[y][x] = ' ';
            }
        }
    }

    void Print() {
        for (size_t y = 0; y < size; ++y) {
            for (size_t x = 0; x < size; ++x) {
                std::cout << grid[y][x];
            }
            std::cout << std::endl;
        }
    }

    void Insert(const int x, const int y, char c) {
        grid[y][x] = c;
    }

    void moveRobot(std::pair<int, int> direction) {
        std::string memory = "";
        std::vector<std::pair<int, int>> positions;
        char* ptrChar = nullptr;
        std::pair<int, int> lookAhead = robotPosition;

        while (true) {
            lookAhead.first += direction.first;
            lookAhead.second += direction.second;
            ptrChar = &grid[lookAhead.second][lookAhead.first];

            if (*ptrChar == '#') {
                // do not move as hit the wall
                break;
            } else if (*ptrChar == 'O') {
                memory += *ptrChar;
                positions.push_back(lookAhead);
            } else if (*ptrChar == '.') {
                // move to new location
                size_t index = 0;
                for (auto position : positions) {
                    grid[position.second + direction.second][position.first + direction.first] = (char)memory[index];
                    ++index;
                }

                // reinstate robot position
                grid[robotPosition.second][robotPosition.first] = '.';
                robotPosition.first += direction.first;
                robotPosition.second += direction.second;
                break;
            }
        }

        grid[robotPosition.second][robotPosition.first] = '@';

        // std::cout << direction.first << " " << direction.second << std::endl;
        // Print();  // debug
    }

    long countBoxes() {
        long count = 0;
        for (size_t y = 0; y < size; ++y) {
            for (size_t x = 0; x < size; ++x) {
                if (grid[y][x] == 'O') {
                    count += y * 100 + x;
                }
            }
        }

        return count;
    }
};

inline long Solver::Solve_Day15_part1() {
    std::string line;
    PlayField playField;

    // build playfield
    int nColumn = 0;
    while (std::getline(file, line) && line != "") {
        for (int index = 0; index < line.length(); index++) {
            char c = (char)line[index];
            playField.Insert(index, nColumn, c);

            // insert position of Robot
            if (c == '@') {
                playField.robotPosition = std::make_pair(index, nColumn);
            }
        }
        ++nColumn;
    }

    playField.Print();  // debug

    // perform move commands
    std::map<char, std::pair<int, int>> commands = {{'^', {0, -1}}, {'>', {1, 0}}, {'<', {-1, 0}}, {'v', {0, 1}}};
    while (std::getline(file, line)) {
        std::pair<int, int> movingDirection;
        for (char command : line) {
            movingDirection = commands[command];
            playField.moveRobot(movingDirection);
        }
    }

    int result = playField.countBoxes();
    playField.Print();  // debug

    return result;
}

#endif