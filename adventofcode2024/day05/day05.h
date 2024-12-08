#ifndef DAY05_H
#define DAY05_H

#include "../utils2024.h"

inline long Solver::Solve_Day05_part1() {
    std::string line;
    std::istringstream iss;
    std::map<int, std::vector<int>> rules;
    long solution = 0;

    // build rules legend
    int row = 0, cols = 0;
    while (std::getline(file, line, '\n') && !line.empty()) {
        iss = std::istringstream(line);
        std::string token;
        int key = 0, value = 0;

        std::getline(iss, token, '|');
        key = std::stoi(token);

        std::getline(iss, token, '|');
        value = std::stoi(token);

        rules[key].push_back(value);
    }

    // correct lines order and match to check if unchanged
    while (std::getline(file, line)) {
        iss = std::istringstream(line);
        std::string token;
        std::vector<int> unsorted;
        std::vector<int> sorted;
        bool isValid = false;

        while (std::getline(iss, token, ',')) {
            int value = std::stoi(token);
            unsorted.push_back(value);
            auto it = sorted.begin();

            while (it != sorted.end()) {
                bool valueGoesBefore = std::find(rules[value].begin(), rules[value].end(), *it) != rules[value].end();
                bool valueGoesAfter = std::find(rules[*it].begin(), rules[*it].end(), value) != rules[value].end();
                if (valueGoesBefore) {
                    break;
                }
                it++;
            }
            sorted.insert(it, value);
        }

        // add mid values only if sorted values are on the same order as the originals
        if (std::equal(sorted.begin(), sorted.end(), unsorted.begin())) {
            solution += sorted.at(sorted.size() / 2);
        }
    }

    return solution;
}

inline long Solver::Solve_Day05_part2() {
    std::string line;
    std::istringstream iss;
    std::map<int, std::vector<int>> rules;
    long solution = 0;

    // build rules legend
    int row = 0, cols = 0;
    while (std::getline(file, line, '\n') && !line.empty()) {
        iss = std::istringstream(line);
        std::string token;
        int key = 0, value = 0;

        std::getline(iss, token, '|');
        key = std::stoi(token);

        std::getline(iss, token, '|');
        value = std::stoi(token);

        rules[key].push_back(value);
    }

    // correct lines order and match to check if unchanged
    while (std::getline(file, line)) {
        iss = std::istringstream(line);
        std::string token;
        std::vector<int> unsorted;
        std::vector<int> sorted;
        bool isValid = false;

        while (std::getline(iss, token, ',')) {
            int value = std::stoi(token);
            unsorted.push_back(value);
            auto it = sorted.begin();

            while (it != sorted.end()) {
                bool valueGoesBefore = std::find(rules[value].begin(), rules[value].end(), *it) != rules[value].end();
                bool valueGoesAfter = std::find(rules[*it].begin(), rules[*it].end(), value) != rules[value].end();
                if (valueGoesBefore) {
                    break;
                }
                it++;
            }
            sorted.insert(it, value);
        }

        // add mid values only if sorted values are on the same order as the originals
        if (!std::equal(sorted.begin(), sorted.end(), unsorted.begin())) {
            solution += sorted.at(sorted.size() / 2);
        }
    }

    return solution;
}

#endif  // DAY05_H