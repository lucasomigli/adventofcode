#ifndef DAY19_H
#define DAY19_H

#ifndef UTILS_H
#include "../utils.h"
#endif

std::string SearchLetters(size_t index,
                          std::map<size_t, std::array<std::vector<int>, 2> > &map,
                          std::map<size_t, char> &letters) {
    // if the index corresponds to a letter (like "a" or "b")
    if (letters.contains(index)) {
        return std::string(1, letters[index]);
    }

    // construct regex pattern based on rules in `map`
    std::string result = "("; // Start with an open parenthesis for grouping
    const auto &options = map[index];

    // process each option (each set of rules separated by '|')
    for (size_t i = 0; i < options.size(); ++i) {
        for (int ruleIndex: options[i]) {
            result += SearchLetters(ruleIndex, map, letters);
        }
        // add '|' to separate options if there are multiple
        if (i < options.size() - 1) {
            result += "|";
        }
    }
    result += ")";

    return result; // Return the constructed regex pattern
}

inline int Solver::Solve_day_19_part1() {
    std::string line;
    std::map<size_t, std::array<std::vector<int>, 2> > map;
    std::map<size_t, char> letters;

    // sort rules to memory
    size_t pos = 0;
    while (std::getline(file, line) && !line.empty()) {
        std::istringstream stream(line);
        std::string token;

        // get first token with format 'N:' as index for map
        stream >> token;
        token.erase(token.end()--);
        pos = static_cast<size_t>(std::stoi(token));

        std::array<std::vector<int>, 2> v;
        auto *ptr = &v[0];
        while (stream >> token) {
            if (token == "|") {
                // if delimiter, pointer advances to new position in the array
                ptr++;
                continue;
            }
            if (token == "\"a\"" || token == "\"b\"") {
                // else if letter add letter to letters as char
                letters[pos] = token[1];
                continue;
            }
            ptr->push_back(std::stoi(token));
        }
        map[pos] = v;
        ++pos;
    }

    std::string str = "";
    str = "^" + SearchLetters(0, map, letters) + "$";
    std::regex re(str);

    // check inputs against rules
    int validLines = 0;
    while (std::getline(file, line) && !line.empty()) {
        validLines += std::regex_match(line, re);
    }


    return validLines;
}


std::string SearchLetters2(size_t index,
                           std::map<size_t, std::array<std::vector<int>, 2> > &map,
                           std::map<size_t, char> &letters,
                           int maxRecursionDepth = 5) {
    if (letters.contains(index)) {
        return std::string(1, letters[index]);
    }

    // special handling for rules 8 and 11 for recursive matching in part 2
    if (index == 8) {
        // Rule 8 is effectively 42+
        std::string rule42 = SearchLetters2(42, map, letters);
        std::string result = "(";
        for (int i = 1; i <= maxRecursionDepth; ++i) {
            if (i > 1) result += "|";
            result += std::string(i, ' ') + rule42;
        }
        result += ")";
        return result;
    } else if (index == 11) {
        // rule 11 is effectively 42{n} 31{n} for n = 1, 2, ..., maxRecursionDepth
        std::string rule42 = SearchLetters(42, map, letters);
        std::string rule31 = SearchLetters(42, map, letters);
        std::string result = "(";
        for (int i = 1; i <= maxRecursionDepth; ++i) {
            if (i > 1) result += "|";
            result += "(" + std::string(i, ' ') + rule42 + std::string(i, ' ') + rule31 + ")";
        }
        result += ")";
        return result;
    }

    // Construct regex pattern based on rules in `map`
    std::string result = "(";
    const auto &options = map[index];

    for (size_t i = 0; i < options.size(); ++i) {
        for (int ruleIndex: options[i]) {
            result += SearchLetters2(ruleIndex, map, letters);
        }
        if (i < options.size() - 1) {
            result += "|";
        }
    }
    result += ")";
    return result;
}

inline int Solver::Solve_day_19_part2() {
    std::string line;
    std::map<size_t, std::array<std::vector<int>, 2> > map;
    std::map<size_t, char> letters;

    // parse rules into memory as before
    size_t pos = 0;
    while (std::getline(file, line) && !line.empty()) {
        std::istringstream stream(line);
        std::string token;

        stream >> token;
        token.erase(token.end()--);
        pos = static_cast<size_t>(std::stoi(token));

        std::array<std::vector<int>, 2> v;
        auto *ptr = &v[0];
        while (stream >> token) {
            if (token == "|") {
                ptr++;
                continue;
            }
            if (token == "\"a\"" || token == "\"b\"") {
                letters[pos] = token[1];
                continue;
            }
            ptr->push_back(std::stoi(token));
        }
        map[pos] = v;
        ++pos;
    }

    // build regex for rule 0 using modified SearchLetters function
    int maxRecursionDepth = 5; // maxrecursion is used
    std::string str = "^" + SearchLetters2(0, map, letters, maxRecursionDepth) + "$";
    std::cout << str[str.size() - 3] << std::endl;
    str = str.substr(0, str.size() - 3) + str.substr(str.size() - 2, str.size());
    std::regex re(str);
    std::cout << "Regex: " << str << std::endl;

    // Check inputs against rules
    int validLines = 0;
    while (std::getline(file, line) && !line.empty()) {
        validLines += std::regex_match(line, re);
    }

    return validLines;
}


#endif //DAY19_H
