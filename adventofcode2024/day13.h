#ifndef DAY13_H
#define DAY13_H

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

inline int findCheapestButtonCount(long targetX, long targetY, const Button& buttonA, const Button& buttonB, const long maxCount = 100) {
    long minCost = __LONG_MAX__;

    for (const Button& button : {buttonA, buttonB}) {
        long currentX = 0, currentY = 0;
        long count = 0;

        while (count < maxCount && currentX <= targetX && currentY <= targetY) {
            // Increment position with current button
            currentX += button.X;
            currentY += button.Y;
            ++count;

            // Calculate the remaining steps for the other button
            const Button& otherButton = (button.type == 'B') ? buttonA : buttonB;
            long remainingX = targetX - currentX;
            long remainingY = targetY - currentY;

            if (remainingX % otherButton.X == 0 && remainingY % otherButton.Y == 0) {
                long targetCountX = remainingX / otherButton.X;
                long targetCountY = remainingY / otherButton.Y;

                if (targetCountX == targetCountY) {
                    long totalCost = count * button.cost + targetCountX * otherButton.cost;
                    minCost = minCost < totalCost ? minCost : totalCost;
                }
            }
        }
    }

    return minCost == __LONG_MAX__ ? 0 : minCost;  // return 0 if no valid solution found
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
        }
    }

    return tokens;
}

inline int Solver::Solve_Day13_part2() {
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
            int cheapestCount = findCheapestButtonCount(target.X, target.Y, A, B, 100000000000);
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

        long m = ptrButton->type == 'T' ? 10000000000000 : 0;
        *ptrButton = Button(ptrButton->X + m, ptrButton->Y + m, ptrButton->type);
    }

    return tokens;
}

#endif
