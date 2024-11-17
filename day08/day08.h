#ifndef UTILS_H
#include "utils.h"
#endif

class Day_8_Solver : public Solver {
 private:
  bool isPart2 = true;
  std::string line;
  int accumulator = 0;
  int position = 1;
  std::string cmd;
  int value = 0;
  std::regex re = std::regex("([a-z]{3}) ([+-]\\d+)");
  std::map<int, std::pair<std::string, int>> commands;
  std::set<int> memory;
  bool hasEnded = false;
  bool swapped = false;
  std::vector<int> swappedCommands;

 public:
  Day_8_Solver(const std::string &_fileInput) : Solver(_fileInput) {}

  void resetState() {
    accumulator = 0;
    position = 1;
    memory.clear();
    swapped = false;
  }

  bool getCommandFromMemory(const int &pos) {
    bool hasCommand = false;
    if (commands.find(pos) != commands.end()) {
      cmd = commands.at(pos).first;
      value = commands.at(pos).second;

      bool alreadySwapped =
          std::find(swappedCommands.begin(), swappedCommands.end(), pos) !=
          swappedCommands.end();

      std::cout << "DEBUG " << pos << " " << cmd << " " << value
                << " alreadySwapped: " << alreadySwapped
                << " swapped: " << swapped << std::endl;
      if (isPart2 && !alreadySwapped && !swapped) {
        if (cmd == "jmp" || (cmd == "nop" && value != 0)) {
          cmd = (cmd == "jmp") ? "nop" : "jmp";
          swappedCommands.push_back(pos);
          swapped = true;
          std::cout << "DEBUG - Changed to " << cmd << std::endl;
        }
      }

      hasCommand = true;
    } else {
      hasCommand = false;
      hasEnded = true;
    }
    return hasCommand;
  }

  void next() {
    if (memory.count(position) == 0) {
      memory.insert(position);
      getCommandFromMemory(position);
      doCommand(cmd, value);
    } else {
      // If position was visited before, we are in an infinite loop.
      throw std::runtime_error("Infinite loop detected");
    }
  }

  void jmp(const int &n) { position += n; }

  void acc(const int &n) {
    accumulator += n;
    ++position;  // Move to next line after `acc`
  }

  void nop() {
    ++position;  // `nop` just moves to the next line
  }

  void doCommand(const std::string &cmd, const int &n) {
    if (cmd == "acc") {
      acc(n);
    } else if (cmd == "jmp") {
      jmp(n);
    } else if (cmd == "nop") {
      nop();
    }
  }

  void parseCommand() {
    std::smatch match;
    if (std::regex_search(line, match, re)) {
      cmd = match[1].str();
      value = std::stoi(match[2].str());
    }
  }

  void loadToMemory() {
    position = 1;
    while (std::getline(file, line)) {
      parseCommand();
      commands[position] = {cmd, value};
      ++position;
    }
    position = 1;  // Reset position to start for execution
  }

  int findSolution() {
    resetState();
    try {
      while (hasEnded == false) {
        next();
      }
    } catch (const std::runtime_error &e) {
      std::cout << "Infinite loop detected at position " << position
                << ". Returning accumulator from last unique position."
                << std::endl;
      resetState();
      return accumulator;
    }
    return accumulator;  // Will not reach here due to loop, but kept for safety
  }

  int findFix() {
    loadToMemory();
    int solution = 0;
    while (hasEnded == false) {
      solution = findSolution();
    };
    return solution;
  }
};
