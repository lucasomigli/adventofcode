#ifndef DAY18_H
#define DAY18_H

#ifndef UTILS_H
#include "../utils.h"
#endif

inline long operate(long &a, const long &b, const char opr) {
    if (opr == '+') {
        a += b;
    } else if (opr == '*') {
        a *= b;
    }
    return a;
}

inline void getInput(const std::string &token, long stack[], char stackOpr[], size_t &pos) {
    if (token.size() == 1 && std::isdigit(token[0])) {
        stack[pos] = operate(stack[pos], std::stol(token), stackOpr[pos]);
    } else if (token.size() == 1 && !std::isdigit(token[0])) {
        stackOpr[pos] = token[0];
    } else if (token.size() >= 2) {
        bool openParenthesis = false;
        for (const char &i: token) {
            if (i == '(') {
                pos++;
                stack[pos] = 0;
                stackOpr[pos] = '+';
                openParenthesis = true;
            } else if (i == ')') {
                stack[pos - 1] = operate(stack[pos - 1], stack[pos], stackOpr[pos - 1]);
                stack[pos] = 0;
                openParenthesis = false;
                pos--;
            } else {
                if (openParenthesis) {
                    stack[pos] = static_cast<long>(i) - 48;
                } else {
                    long tmp = static_cast<long>(i) - 48;
                    stack[pos] = operate(stack[pos], tmp, stackOpr[pos]);
                }
            }
        }
    }
}

inline long Solver::Solve_day_18_part1() {
    std::string line;
    long stack[64];
    char stackOpr[64];
    long sum = 0;

    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string token;
        size_t pos = 0;
        stack[0] = 0;
        stackOpr[0] = '+';
        while (lineStream >> token) {
            getInput(token, stack, stackOpr, pos);
        }
        sum += stack[0];
    }

    return sum;
}

inline std::string addParenthesis(std::string &line) {
    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == '+') {
            size_t pos = i - 2;
            int parenthesisCount = 0;
            if (std::isdigit(line[pos])) {
                // Add a '(' before the index
                line = line.substr(0, pos) + "(" + line.substr(pos, line.size());
                i++;
            } else {
                while (true) {
                    if (line[pos] == ')') { --parenthesisCount; } else if (line[pos] == '(') { ++parenthesisCount; }
                    if (line[pos] == '(' && parenthesisCount == 0) { break; }
                    pos--;
                }
                line = line.substr(0, pos + 1) + "(" + line.substr(pos + 1, line.size());
                i++;
            }

            pos = i + 2;
            if (std::isdigit(line[pos])) {
                // Add a ')' after the index
                line = line.substr(0, pos + 1) + ")" + line.substr(pos + 1, line.size());
                i++;
            } else {
                parenthesisCount = 0;
                while (true) {
                    if (line[pos] == '(') { --parenthesisCount; } else if (line[pos] == ')') { ++parenthesisCount; }
                    if (line[pos] == ')' && parenthesisCount == 0) { break; }
                    pos++;
                }
                line = line.substr(0, pos) + ")" + line.substr(pos, line.size());
                i++;
            }
        }
    }
    return line;
}

inline long Solver::Solve_day_18_part2() {
    std::string line;
    long stack[64];
    char stackOpr[64];
    long sum = 0;

    while (std::getline(file, line)) {
        // Add parenthesis to line, grouping sum operations before others.
        addParenthesis(line);
        std::istringstream lineStream(line);
        std::string token;
        size_t pos = 0;
        stack[0] = 0;
        stackOpr[0] = '+';
        while (lineStream >> token) {
            // run through the same solution as with part1, on a modified line.
            getInput(token, stack, stackOpr, pos);
        }
        sum += stack[0];
    }

    return sum;
}

#endif //DAY18_H
