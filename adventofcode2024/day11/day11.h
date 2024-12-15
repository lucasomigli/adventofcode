#ifndef DAY11_H
#define DAY11_H

#include <queue>
#include <unordered_map>

#include "../utils2024.h"

// Cache to store results of transformations
std::unordered_map<std::string, std::vector<std::string>> cache;

std::string removeLeadingZeros(const std::string& st) {
    long _n = std::stol(st);
    return std::to_string(_n);
}

std::vector<std::string> transform(const std::string& input) {
    // Check cache
    if (cache.find(input) != cache.end()) {
        return cache[input];
    }

    std::vector<std::string> transformed;
    long input_n = std::stol(input);

    if (input_n == 0) {
        transformed = {"1"};
    } else if (input.size() % 2 == 0) {
        std::string left = input.substr(0, input.size() / 2);
        std::string right = removeLeadingZeros(input.substr(input.size() / 2));
        transformed.push_back(left);
        transformed.push_back(right);
    } else {
        transformed = {std::to_string(input_n * 2024)};
    }

    // Cache result
    cache[input] = transformed;
    return transformed;
}

inline long Solver::Solve_Day11_part1() {
    std::string token;
    std::getline(std::ifstream(this->fileInput), token);
    std::istringstream ss(token);
    std::queue<std::string> queue;

    long max_counter = 75;

    // Initialize queue
    while (ss >> token) {
        queue.push(token);
    }

    long counter = 0;

    while (!queue.empty() && counter < max_counter) {
        long currentSize = queue.size();

        for (long i = 0; i < currentSize; ++i) {
            std::string item = queue.front();
            queue.pop();

            std::vector<std::string> transformed = transform(item);
            for (const auto& t : transformed) {
                queue.push(t);
            }
        }

        ++counter;
    }

    return queue.size();
}

#endif
