#ifndef DAY03_2024_H
#define DAY03_2024_H

#include "../utils2024.h"

inline long Solver::Solve_Day03_part1() {
    std::string line;
    std::regex re(R"~(mul\((\d+)\,(\d+)\))~");
    long result = 0;

    while (std::getline(file, line)) {
        std::sregex_iterator iter(line.begin(), line.end(), re);
        std::sregex_iterator end;

        while (iter != end) {
            int multiplication = 1;
            for (unsigned i = 1; i < iter->size(); ++i) {
                multiplication *= std::stoi((*iter)[i]);
            }
            result += multiplication;
            ++iter;
        }
    }

    return result;
}

inline inline long Solver::Solve_Day03_part2() {
    std::string line;
    long result = 0;
    std::regex re(R"(^mul\((\d+),(\d+)\))");
    bool enabled = true;

    while (std::getline(file, line)) {
        size_t pos = 0;
        std::string segment;
        while (pos < line.size()) {
            if (line.substr(pos, 7) == "don't()") {
                // enable and go up 7 positions for "don't()"
                enabled = false;
                pos += 7;
            } else if (line.substr(pos, 4) == "do()") {
                // enable and go up 4 positions for "do()"
                enabled = true;
                pos += 4;
            } else if (line.substr(pos, 4) == "mul(") {
                if (enabled) {
                    std::smatch match;
                    // search only the segment substring starting from "pos" to the end of the line
                    segment = line.substr(pos);
                    if (std::regex_search(segment, match, re)) {
                        int a = std::stoi(match[1]);
                        int b = std::stoi(match[2]);
                        result += a * b;
                        pos += match[0].length();
                    } else {
                        ++pos;
                    }
                } else {
                    pos += 4; // jump only up the same length as the match "mul("
                }
            } else {
                ++pos; // go up one position as nothing was matched
            }
        }
    }

    return result;
}

#endif //DAY03_2024_H
