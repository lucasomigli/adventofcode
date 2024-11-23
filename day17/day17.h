#ifndef DAY17_H
#define DAY17_H

#ifndef UTILS_H
#include "../utils.h"
#endif

inline long Solver::Solve_day_17_part1() {
    std::string line;
    std::vector<long> stack;

    while (std::getline(file, line)) {
        std::istringstream linestream(line);
        std::cout << line << std::endl;

        std::string token;
        char opr;
        long n = 0;
        bool start = true;
        while (linestream >> token) {
            if (token.size() == 1 && std::isdigit(token[0])) {
                if (opr == '+') {
                    n += std::stol(token);
                } else if (opr == '*') {
                    n *= std::stol(token);
                }
            } else if (token.size() == 1 && !std::isdigit(token[0])) {
                opr = token[0];
            } else if (token.size() >= 2 && std::isdigit(token[0])) {
                // closing parenthesis
            } else if (token.size() >= 2 && !std::isdigit(token[0])) {
                // opening parenthesis
            }
        }
    }
}

#endif //DAY17_H
