#include "utils2024.h"

struct Robot {
    int x, y;
    int xVelocity, yVelocity;

    Robot() {
        x = 0;
        y = 0;
        xVelocity = 0;
        yVelocity = 0;
    };

    Robot(int _x, int _y, int _xVelocity, int _yVelocity) {
        x = _x;
        y = _y;
        xVelocity = _xVelocity;
        yVelocity = _yVelocity;
    }

    void Move(int n = 1, int xLimit = 101, int yLimit = 103) {
        for (int i = 0; i < n; ++i) {
            int newX = x + xVelocity, newY = y + yVelocity;

            if (newX >= 0) {
                x = newX >= xLimit ? newX - xLimit : newX;
            } else {
                x = newX < 0 ? newX + xLimit : newX;
            }

            if (newY >= 0) {
                y = newY >= yLimit ? newY - yLimit : newY;
            } else {
                y = newY < 0 ? newY + yLimit : newY;
            }
        }
    }

    void Print() {
        std::cout << "x: " << x << " "
                  << "y: " << y << " "
                  << "xVelocity: " << xVelocity << " "
                  << "yVelocity: " << yVelocity << " "
                  << std::endl;
    }
};

inline int Solver::Solve_Day14_part1() {
    std::string line;
    int safetyFactor = 0;
    std::regex position(R"(p\=(-?\d*)\,(-?\d*))");
    std::regex velocity(R"(v\=(-?\d*)\,(-?\d*))");
    int quadrants[4] = {0, 0, 0, 0};

    int xLimit = 101, yLimit = 103;
    // xLimit = 7, yLimit = 11;  // test

    while (std::getline(file, line)) {
        Robot p;
        std::cout << line << std::endl;  // debug

        std::smatch sm;
        std::regex_search(line, sm, position);

        int x = std::stoi(sm[1].str());
        int y = std::stoi(sm[2].str());

        std::regex_search(line, sm, velocity);
        int xVel = std::stoi(sm[1].str());
        int yVel = std::stoi(sm[2].str());

        p = Robot(x, y, xVel, yVel);
        p.Print();
        // p.Move(100, 11, 7);  // test
        p.Move(100);  // input

        // check quadrants
        if (p.x < xLimit / 2 && p.y < yLimit / 2) {
            ++quadrants[0];
        } else if (p.x < xLimit / 2 && p.y > yLimit / 2) {
            ++quadrants[1];
        } else if (p.x > xLimit / 2 && p.y > yLimit / 2) {
            ++quadrants[2];
        } else if (p.x > xLimit / 2 && p.y < yLimit / 2) {
            ++quadrants[3];
        }
        p.Print();
    }

    safetyFactor = quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3];

    return safetyFactor;
}

struct Grid {
    char grid[103][101];
    Grid() {
        for (size_t y = 0; y < 103; ++y) {
            for (size_t x = 0; x < 101; ++x) {
                grid[y][x] = ' ';
            }
        }
    }

    void Print() {
        for (size_t y = 0; y < 103; ++y) {
            for (size_t x = 0; x < 101; ++x) {
                std::cout << grid[y][x];
            }
            std::cout << std::endl;
        }
    }

    bool isChristmasTree() {
        size_t offset = 10;
        for (size_t x = offset; x < 101 - offset; ++x) {
            for (size_t y = offset; y < 103 - offset; ++y) {
                if (grid[y][x] == '#' && grid[y + 1][x] == '#' && grid[y + 2][x] == '#' &&
                    grid[y + 3][x] == '#' && grid[y + 4][x] == '#' && grid[y + 5][x] == '#' &&
                    grid[y + 6][x] == '#' && grid[y + 7][x] == '#' && grid[y + 8][x] == '#') {
                    return true;  // return true if found consecutive hashes
                }
            }
        }

        return false;
    }

    void Insert(const int x, const int y) {
        grid[y][x] = '#';
    }

    void Clear() {
        Grid tmp;
        *this = tmp;
    }
};

inline int Solver::Solve_Day14_part2() {
    std::string line;
    std::regex position(R"(p\=(-?\d*)\,(-?\d*))");
    std::regex velocity(R"(v\=(-?\d*)\,(-?\d*))");
    Grid grid;

    int maxIterations = 100000;

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        while (std::getline(file, line)) {
            Robot p;

            std::smatch sm;
            std::regex_search(line, sm, position);

            int x = std::stoi(sm[1].str());
            int y = std::stoi(sm[2].str());

            std::regex_search(line, sm, velocity);
            int xVel = std::stoi(sm[1].str());
            int yVel = std::stoi(sm[2].str());

            p = Robot(x, y, xVel, yVel);
            p.Move(iteration);  // input

            // insert into grid
            grid.Insert(p.x, p.y);
        }

        // check if grid has 5 robots on line and print.
        if (grid.isChristmasTree()) {
            grid.Print();
            std::cout << "Is valid tree: " << iteration << std::endl;
            return iteration;
        }

        // get back to the beginning of file
        grid.Clear();
        file.clear();
        file.seekg(0);
    }

    return 0;
}