#ifndef DAY07_H
#define DAY07_H

#include "../utils2024.h"

inline long Solver::Solve_Day07_part1() {
    std::string line;
    std::vector<long> combinations;
    long result = 0;

    while (std::getline(file, line)) {
        std::string token;
        std::istringstream iss(line);

        // get result target first
        iss >> token;
        long target = std::stol(token.substr(0, token.size()));

        // get values into vector
        std::vector<long> tmp;
        while (iss >> token) {
            long val = std::stol(token);
            if (combinations.size() == 0) {
                combinations.push_back(val);
                continue;
            }

            for (long &el : combinations) {
                long addition = el + val;
                long multiplication = el * val;

                tmp.push_back(addition);
                tmp.push_back(multiplication);
            }
            combinations = tmp;
            tmp.clear();
        }

        for (long &value : combinations) {
            if (value == target) {
                result += target;
                break;
            }
        }

        combinations.clear();
    }

    return result;
}

inline long Solver::Solve_Day07_part2() {
    std::string line;
    std::vector<long> combinations;
    long result = 0;

    while (std::getline(file, line)) {
        std::string token;
        std::istringstream iss(line);

        // get result target first
        iss >> token;
        long target = std::stol(token.substr(0, token.size()));

        // get values into vector
        std::vector<long> tmp;
        while (iss >> token) {
            long val = std::stol(token);
            if (combinations.size() == 0) {
                combinations.push_back(val);
                continue;
            }

            for (long &el : combinations) {
                long addition = el + val;
                long multiplication = el * val;
                long concatenation = std::stol(std::to_string(el) + std::to_string(val));

                tmp.push_back(addition);
                tmp.push_back(multiplication);
                tmp.push_back(concatenation);
            }
            combinations = tmp;
            tmp.clear();
        }

        for (long &value : combinations) {
            if (value == target) {
                result += target;
                break;
            }
        }

        combinations.clear();
    }

    return result;
}

#endif  // DAY07_H
