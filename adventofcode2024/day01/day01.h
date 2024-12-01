#ifndef DAY01_2024_H
#define DAY01_2024_H

#ifndef UTILS_H
#include "../utils2024.h"
#endif

inline int Solver::Solve_Day01_part1() {
    std::string line;
    int differences = 0;
    std::multiset<int> left;
    std::multiset<int> right;

    // insert numbers into two sets (left and right) in order.
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        // insert number into the left multiset
        iss >> token;
        left.insert(std::stoi(token));

        // insert number into the right multiset
        iss >> token;
        right.insert(std::stoi(token));
    }

    // calculate differences
    int index = 0;
    for (auto it = left.begin(); it != left.end(); ++it) {
        index = std::distance(left.begin(), it);
        auto it2 = std::next(right.begin(), index);
        differences += std::abs(*it - *it2);
    }

    return differences;
}

inline int Solver::Solve_Day01_part2() {
    std::string line;
    int differences = 0;
    std::vector<int> left;
    std::map<int, int> right;

    // insert numbers into two sets (left and right) in order.
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        // insert number into the left vector
        iss >> token;
        left.push_back(std::stoi(token));

        // insert number into the right map
        iss >> token;
        right[std::stoi(token)] += 1;
    }

    // increase similarity score for each item in the left vector
    for (auto it = left.begin(); it != left.end(); ++it) {
        differences += right[*it] * *it;
    }

    return differences;
}


#endif //DAY01_2024_H
