#include <cmath>
#include <limits>
#include <numeric>
#include <optional>
#include <utility>

#include "utils2024.h"

struct Button {
    long X, Y = (0, 0);
    char type = 'A';
    int cost = 0;

    Button() {};
    Button(char _type) {
        type = _type;
    }
    Button(long _X, long _Y, char _type) {
        X = _X;
        Y = _Y;
        type = _type;
        cost = type == 'A' ? 3 : 1;
    }
};

// Solves a system of two linear equations using Cramer's Rule
std::optional<std::pair<long, long>> solveLinearSystem(long a_x, long b_x, long targetX, long a_y, long b_y, long targetY) {
    long determinant = a_x * b_y - a_y * b_x;
    if (determinant == 0) {
        return std::nullopt;  // No unique solution
    }

    long numeratorA = targetX * b_y - targetY * b_x;
    long numeratorB = targetY * a_x - targetX * a_y;

    // compute integer solutions
    long a = numeratorA / determinant;
    long b = numeratorB / determinant;

    // check if the solutions make sense (e.g., integers, non-negative button presses)
    if (a < 0 || b < 0 || numeratorA % determinant != 0 || numeratorB % determinant != 0) {
        return std::nullopt;  // No feasible solution
    }

    return std::make_pair(a, b);
}

inline long findCheapestButtonCount(long targetX, long targetY, const Button& buttonA, const Button& buttonB, const long maxCount = 100) {
    long minCost = __LONG_MAX__;

    // Coefficients for the system of equations
    long a_x = buttonA.X, b_x = buttonB.X;
    long a_y = buttonA.Y, b_y = buttonB.Y;

    // Solve the system of equations
    auto solution = solveLinearSystem(a_x, b_x, targetX, a_y, b_y, targetY);

    if (solution) {
        long A = solution->first;   // number of times button A is pressed
        long B = solution->second;  // number of times button B is pressed

        // ensure the solution is valid
        if (A >= 0 && B >= 0 && A <= maxCount && B <= maxCount) {
            // Calculate the cost
            long cost = A * buttonA.cost + B * buttonB.cost;
            minCost = std::min(minCost, cost);
        }
    }

    return minCost == __LONG_MAX__ ? 0 : minCost;  // Return 0 if no valid solution found
}
inline int Solver::Solve_Day13_part1() {
    std::string line;
    int tokens = 0;
    std::regex left("(Button (A|B))|(Prize)");
    std::regex right(R"((X|Y)(\+|\=)(\d*))");

    Button A = Button('A');
    Button B = Button('B');
    Button target = Button('T');

    Button* ptrButton = new Button();

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string s;
        std::cout << line << std::endl;  // debug

        // get left hand side first before the ':'
        std::getline(iss, s, ':');
        std::smatch sm;
        std::regex_match(s, sm, left);

        if (s == "Button A") {
            ptrButton = &A;
        } else if (s == "Button B") {
            ptrButton = &B;
        } else {
            ptrButton = &target;
        }

        // right hand side after the ':'
        std::getline(iss, s, ':');
        for (std::smatch sm; std::regex_search(s, sm, right);) {
            char c = sm[1].str()[0];
            if (c == 'X') {
                ptrButton->X = std::stoi(sm[3].str());
            } else if (c == 'Y') {
                ptrButton->Y = std::stoi(sm[3].str());
            }
            s = sm.suffix();
        }
        *ptrButton = Button(ptrButton->X, ptrButton->Y, ptrButton->type);

        if (line == "") {
            int cheapestCount = findCheapestButtonCount(target.X, target.Y, A, B);
            tokens += cheapestCount;
            std::cout << cheapestCount << std::endl;  // debug
        }
    }

    return tokens;
}

inline long Solver::Solve_Day13_part2() {
    std::string line;
    long tokens = 0;
    std::regex left("(Button (A|B))|(Prize)");
    std::regex right(R"((X|Y)(\+|\=)(\d*))");

    Button A = Button('A');
    Button B = Button('B');
    Button target = Button('T');

    Button* ptrButton = new Button();

    while (std::getline(file, line)) {
        std::cout << line << std::endl;  // debug

        std::istringstream iss(line);
        std::string s;

        if (line == "") {
            long cheapestCount = findCheapestButtonCount(target.X, target.Y, A, B, __LONG_MAX__);
            tokens += cheapestCount;
            std::cout << cheapestCount << std::endl;  // debug
            continue;
        }

        // get left hand side first before the ':'
        std::getline(iss, s, ':');
        std::smatch sm;
        std::regex_match(s, sm, left);

        if (s == "Button A") {
            ptrButton = &A;
        } else if (s == "Button B") {
            ptrButton = &B;
        } else {
            ptrButton = &target;
        }

        // right hand side after the ':'
        std::getline(iss, s, ':');
        for (std::smatch sm; std::regex_search(s, sm, right);) {
            char c = sm[1].str()[0];
            if (c == 'X') {
                ptrButton->X = std::stoi(sm[3].str());
            } else if (c == 'Y') {
                ptrButton->Y = std::stoi(sm[3].str());
            }
            s = sm.suffix();
        }

        long m = ptrButton->type == 'T' ? 10'000'000'000'000 : 0;
        *ptrButton = Button(ptrButton->X + m, ptrButton->Y + m, ptrButton->type);
    }

    return tokens;
}
