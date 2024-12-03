#ifndef DAY02_2024_H
#define DAY02_2024_H

#ifndef UTILS_H
#include "../utils2024.h"
#endif

inline int Solver::Solve_Day02_part1() {
    std::string line;
    int currentNumber = 0;
    int previousNumber = 0;
    int currentDifference = 0;
    int totalCount = 0;
    std::vector<int> stack;
    std::pair<int, int> minMax = {1, 3};

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        iss >> token;
        previousNumber = std::stoi(token);
        stack.clear();
        stack.push_back(previousNumber);

        while (iss >> token) {
            currentNumber = std::stoi(token);
            stack.push_back(currentNumber);

            currentDifference = std::abs(currentNumber - previousNumber);
            if (currentDifference < minMax.first || currentDifference > minMax.second) {
                totalCount--;
                break;
            }
            if (stack.size() >= 3) {
                if (stack[2] > stack[1] != stack[1] > stack[0]) {
                    totalCount--;
                    break;
                }
                stack.erase(stack.begin());
            }
            previousNumber = currentNumber;
        }
        totalCount++;
    }
    return totalCount;
}

inline bool checkValid(const std::vector<int> &v, const std::pair<int, int> &minMax) {
    auto isValidSequence = [&](const std::vector<int> &seq) -> bool {
        bool increasing = seq[1] > seq[0];
        for (size_t i = 1; i < seq.size(); ++i) {
            int diff = std::abs(seq[i] - seq[i - 1]);
            if (diff < minMax.first || diff > minMax.second) return false;
            if ((seq[i] > seq[i - 1]) != increasing) return false;
        }
        return true;
    };

    if (isValidSequence(v)) return true;

    // try removing each level once
    for (size_t i = 0; i < v.size(); ++i) {
        std::vector<int> modified = v;
        modified.erase(i + modified.begin());
        if (isValidSequence(modified)) return true;
    }

    return false;
}


inline int Solver::Solve_Day02_part2() {
    std::string line;
    int totalCount = 0;
    std::pair<int, int> minMax = {1, 3};

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<int> levels(std::istream_iterator<int>(ss), {});

        if (checkValid(levels, minMax)) {
            totalCount++;
        };
    }

    return totalCount;
}


#endif //DAY02_2024_H
