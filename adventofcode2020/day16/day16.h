#ifndef DAY16_H
#define DAY16_H

#ifndef UTILS_2020_H
#include "../utils2020.h"
#endif

long long Solver::Solve_day_16_part2() {
    std::string line;
    std::regex regex_field("[a-z ]+:");
    std::regex regex("([0-9]+)-([0-9]+)");
    std::vector<std::vector<std::pair<int, int>>> constrictions;
    std::vector<std::vector<int>> validTickets;
    std::vector<std::string> fields;

    // Parsing fields and constraints
    while (std::getline(file, line) && !line.empty()) {
        std::smatch match;

        // Extract field names
        while (std::regex_search(line, match, regex_field)) {
            fields.push_back(match[0]);
            line = match.suffix();
        }

        // Extract constraint ranges
        std::vector<std::pair<int, int>> pairs;
        while (std::regex_search(line, match, regex)) {
            pairs.emplace_back(std::stoi(match[1]), std::stoi(match[2]));
            line = match.suffix();
        }

        constrictions.push_back(pairs);
    }

    // Parsing tickets
    while (std::getline(file, line)) {
        if (line.empty() || line.find("ticket") != std::string::npos) {
            continue;
        }
        std::stringstream ss(line);
        std::string token;
        int number;
        bool isValidToken = false;
        bool isValidTicket = true;
        std::vector<int> ticket;

        // Parse each ticket value and validate it
        while (std::getline(ss, token, ',')) {
            number = std::stoi(token);
            isValidToken = false;

            // Check against all constraints
            for (const auto& ranges : constrictions) {
                for (const auto& range : ranges) {
                    if (number >= range.first && number <= range.second) {
                        isValidToken = true;
                        break;
                    }
                }
                if (isValidToken) break;
            }

            if (!isValidToken) {
                isValidTicket = false;
                break;
            }

            ticket.push_back(number);
        }

        // Only keep valid tickets
        if (isValidTicket) {
            validTickets.push_back(ticket);
        }
    }

    // Map field positions to their possible valid field names
    std::map<int, std::set<int>> field_positions;

    // Initialize all positions with all fields
    for (int i = 0; i < fields.size(); ++i) {
        field_positions[i] = std::set<int>();
        for (int j = 0; j < fields.size(); ++j) {
            field_positions[i].insert(j);
        }
    }

    // Narrow down possible field positions
    for (const auto& ticket : validTickets) {
        for (int pos = 0; pos < ticket.size(); ++pos) {
            for (int f = 0; f < fields.size(); ++f) {
                bool fits = false;
                for (const auto& range : constrictions[f]) {
                    if (ticket[pos] >= range.first && ticket[pos] <= range.second) {
                        fits = true;
                        break;
                    }
                }
                if (!fits) {
                    field_positions[pos].erase(f);
                }
            }
        }
    }

    // Determine the exact field positions
    std::map<int, int> resolved_fields;
    while (resolved_fields.size() < fields.size()) {
        for (const auto& [pos, possible_fields] : field_positions) {
            if (possible_fields.size() == 1) {
                int field = *possible_fields.begin();
                resolved_fields[pos] = field;

                // Remove the resolved field from other positions
                for (auto& [other_pos, other_fields] : field_positions) {
                    other_fields.erase(field);
                }
            }
        }
    }

    // Calculate the product of fields starting with "departure" from own ticket
    long long product = 1;
    for (const auto& [pos, field_index] : resolved_fields) {
        if (fields[field_index].find("departure") == 0) {
            product *= validTickets[0][pos];
        }
    }

    return product;
}

#endif  // DAY16_H
