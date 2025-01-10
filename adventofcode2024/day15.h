#ifndef DAY15_H
#define DAY15_H

#include "utils2024.h"

struct PlayField {
    const static int size = 10;
    char grid[size][size];
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

struct PlayField2 {
   private:
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> mBoxes;

   public:
    const static int size = 50;
    const static int wideness = size * 2;
    char grid[size][wideness];
    std::pair<int, int> robotPosition = {0, 0};

    PlayField2() {
        for (size_t y = 0; y < size; ++y) {
            for (size_t x = 0; x < wideness; ++x) {
                grid[y][x] = ' ';
            }
        }
    }

    void Print() {
        for (size_t y = 0; y < size; ++y) {
            for (size_t x = 0; x < wideness; ++x) {
                std::cout << grid[y][x];
            }
            std::cout << std::endl;
        }
    }

    void Insert(const int x, const int y, char c) {
        int wideX = x * 2;
        // turn play field into 2 times wider
        if (c == '#' || c == '.') {
            grid[y][wideX] = c;
            grid[y][++wideX] = c;
        } else if (c == 'O') {
            grid[y][wideX] = '[';
            grid[y][++wideX] = ']';
        } else if (c == '@') {
            grid[y][wideX] = c;
            grid[y][++wideX] = '.';

            // insert position of Robot
            robotPosition = std::make_pair(wideX - 1, y);
        }
    }

    bool canMove(std::pair<int, int> direction, std::pair<std::pair<int, int>, std::pair<int, int>> blockPosition) {
        // add block to positions
        mBoxes.push_back(blockPosition);

        bool isLeftValid = true, isRightValid = true;
        bool isVertical = direction.second != 0;
        std::pair<int, int> left, right;

        if (isVertical) {  // if direction is vertical check both left and right
            left = {blockPosition.first.first, blockPosition.first.second + direction.second};
            right = {blockPosition.second.first, blockPosition.second.second + direction.second};
        } else {                         // if horizontal set both to the same position horizontally
            if (direction.first == 1) {  // if direction is to the right
                left = {blockPosition.second.first + direction.first, blockPosition.second.second};
                right = {blockPosition.second.first + direction.first * 2, blockPosition.second.second};
            } else {  // if direction is to the left
                right = {blockPosition.first.first + direction.first, blockPosition.first.second};
                left = {blockPosition.first.first + direction.first * 2, blockPosition.first.second};
            }
        }

        char leftChar = grid[left.second][left.first];
        char rightChar = grid[right.second][right.first];

        if (isVertical) {
            if (leftChar == '#' || rightChar == '#') {
                // if hitting a wall set to invalid
                isLeftValid = false;
            } else {
                // if '.' return true, else for '[' or ']'check the block again, left and right
                isLeftValid = leftChar == '.'   ? true
                              : leftChar == '[' ? canMove(direction, {left, right})
                                                : canMove(direction, {{left.first - 1, left.second}, left});
                isRightValid = rightChar == '.'   ? true
                               : rightChar == ']' ? canMove(direction, {left, right})
                                                  : canMove(direction, {right, {right.first + 1, right.second}});
            }
        } else {
            if ((direction.first == 1 && leftChar == '#') || (direction.first == -1 && rightChar == '#')) {
                // if hitting a wall set to invalid
                isLeftValid = false;
            } else if (leftChar == '.' || rightChar == '.') {
                isLeftValid = true;
            } else {
                isLeftValid = canMove(direction, {left, right});
            }
        }

        return isLeftValid && isRightValid;
    }

    void moveRobot(std::pair<int, int> direction) {
        char* ptrChar = nullptr;
        std::pair<int, int> lookAhead = robotPosition;

        lookAhead.first += direction.first;
        lookAhead.second += direction.second;
        ptrChar = &grid[lookAhead.second][lookAhead.first];

        if (*ptrChar == '#') {
            // do not move as hit the wall [skip]
            return;
        } else if (*ptrChar == '[' || *ptrChar == ']') {
            // if a box is next to the direction, check if robot can push the boxes
            std::pair<std::pair<int, int>, std::pair<int, int>> blockPosition;
            if (*ptrChar == '[') {
                blockPosition = {{lookAhead.first, lookAhead.second}, {lookAhead.first + 1, lookAhead.second}};
            } else {
                blockPosition = {{lookAhead.first - 1, lookAhead.second}, {lookAhead.first, lookAhead.second}};
            }

            if (!canMove(direction, blockPosition)) {
                // clear mBoxes for a new move and return [skip]
                mBoxes.clear();
                return;
            }
        }

        // push boxes if canMove returns true
        if (!mBoxes.empty()) {
            for (auto position : mBoxes) {
                grid[position.first.second][position.first.first] = '.';
                grid[position.second.second][position.second.first] = '.';
            }
            // move each box to the new location starting from the end
            for (auto iterator = mBoxes.rbegin(); iterator != mBoxes.rend(); iterator++) {
                // // flush on grid before writing
                // grid[iterator->first.second][iterator->first.first] = '.';

                // move box
                grid[iterator->first.second + direction.second][iterator->first.first + direction.first] = '[';
                grid[iterator->second.second + direction.second][iterator->second.first + direction.first] = ']';
            }

            // clear mBoxes for a new move
            mBoxes.clear();
        }

        // set new position of the robot
        grid[robotPosition.second][robotPosition.first] = '.';
        robotPosition.first += direction.first;
        robotPosition.second += direction.second;
        grid[robotPosition.second][robotPosition.first] = '@';
    }

    long countBoxes() {
        long count = 0;
        for (size_t y = 0; y < size; ++y) {
            for (size_t x = 0; x < wideness; ++x) {
                if (grid[y][x] == '[') {
                    count += y * 100 + x;
                }
            }
        }

        return count;
    }
};

inline long Solver::Solve_Day15_part2() {
    std::string line;
    PlayField2 playField;

    // build playfield
    int nColumn = 0;
    while (std::getline(file, line) && line != "") {
        for (int index = 0; index < line.length(); index++) {
            char c = (char)line[index];
            playField.Insert(index, nColumn, c);
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
            std::cout << command << std::endl;  // debug
            playField.moveRobot(movingDirection);
            playField.Print();  // debug
        }
    }

    int result = playField.countBoxes();
    playField.Print();  // debug

    return result;
}

#endif