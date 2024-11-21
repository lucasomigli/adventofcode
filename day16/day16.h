#ifndef DAY16_H
#define DAY16_H

#ifndef UTILS_H
#include "../utils.h"
#endif
#include <utility>

int Solver::Solve_day_16_part1() {
  std::string line;
  std::regex regex("([0-9]+)-([0-9]+)");
  std::vector<std::pair<int, int>> constrictions;
  int sum = 0;

  while (std::getline(file, line) && !line.empty()) {
    std::smatch match;

    while (std::regex_search(line, match, regex)) {
      std::pair<int, int> constriction;
      constriction = std::make_pair(std::stoi(match[1]), std::stoi(match[2]));
      constrictions.push_back(constriction);
      line = match.suffix();
    }
  }

  while (std::getline(file, line)) {
    if (line.empty() | line.find("ticket") != std::string::npos) {
      continue;
    }
    std::stringstream ss(line);
    std::string token;
    int number;
    bool isValid = false;
    while (std::getline(ss, token, ',')) {
      number = std::stoi(token);
      for (auto it = constrictions.begin(); it != constrictions.end(); it++) {
          if (number >= (*it).first && number <= (*it).second) {
            isValid = true;
        }
      }
      if (!isValid) {
        sum+=number;
      }
      isValid = false;
    }

  }
  return sum;
}

int Solver::Solve_day_16_part2() {
  std::string line;
  std::regex regex_field("[a-z ]+:");
  std::regex regex("([0-9]+)-([0-9]+)");
  std::vector<std::vector<std::pair<int,int>>> constrictions;
  std::vector<std::vector<int>> validTickets;
  std::vector<std::string> fields;

  while (std::getline(file, line) && !line.empty()) {
    std::smatch match;

    while (std::regex_search(line, match, regex_field)) {
      fields.push_back(match[0]);
      std::cout << fields.back() << std::endl;
      line = match.suffix();
    }

    std::vector<std::pair<int, int>> pairs;
    while (std::regex_search(line, match, regex)) {
      std::pair<int, int> constriction;
      constriction = std::make_pair(std::stoi(match[1]), std::stoi(match[2]));
      pairs.push_back(constriction);
      line = match.suffix();
    }

    constrictions.push_back(pairs);
  }

  while (std::getline(file, line)) {
    if (line.empty() | line.find("ticket") != std::string::npos) {
      continue;
    }
    std::stringstream ss(line);
    std::string token;
    int number;
    bool isValidToken = false;
    bool isValid = true;
    std::vector<int> ticket;

    while (std::getline(ss, token, ',')) {
      number = std::stoi(token);
      for (auto it = constrictions.begin(); it != constrictions.end(); it++) {
        for (auto pair : *it) {
          if (number >= pair.first && number <= pair.second) {
            isValidToken = true;
          }
        }
      }
      if (!isValidToken) {
        isValid = false;
        break;
      }
      ticket.push_back(number);
      isValidToken = false;
    }
    if (isValid) {
      validTickets.push_back(ticket);
    }
  }

  std::string headers[fields.size()];

  for (int fieldPosition = 0; fieldPosition < constrictions.size(); ++fieldPosition) {
    int goodTicketPosition;
    for (int ticketPosition = 0; ticketPosition < validTickets.size(); ++ticketPosition) {
      bool isValidPair = true;
      for (auto it = validTickets.begin(); it != validTickets.end(); it++) {
        isValidPair = true;
        for (int i = 0; i < constrictions[fieldPosition].size(); i++) {
          std::pair<int,int> *currentPair = &constrictions[fieldPosition][i];
          isValidPair = (*it).at(ticketPosition) >= (*currentPair).first &&
          (*it).at(ticketPosition) <= (*currentPair).second;
          // std::cout << (*it).at(ticketPosition) << " " << (*currentPair).first << " " << (*currentPair).second << std::endl;
          if (isValidPair) {
            break;
          }
          isValidPair = false;
        }
        if (!isValidPair) {
          break;
        }
      }
      if (isValidPair) {
        goodTicketPosition = ticketPosition;
      break;
      }
    }
    headers[goodTicketPosition] = fields[fieldPosition];
    std::cout << headers[goodTicketPosition] << "goodTicketPosition = " << goodTicketPosition << " " << fields[fieldPosition]<< std::endl;
  }

  // for (auto h : headers) { std::cout << "DEBUG: " << h << std::endl;}

  // finally get values from own ticket (first) with known headers fields
  long sum = 0;
  for (int index = 0; index < validTickets[0].size(); index++) {
    // std::cout << index << " " << headers[index] << " " << validTickets[0][index] << std::endl;
    if (headers[index].find("departure") != std::string::npos) {
      sum += validTickets[0][index];
    }
  }
  return sum;
}

#endif  // DAY16_H
