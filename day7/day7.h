#ifndef DAY7_H
#define DAY7_H

#ifndef UTILS_H
#include "../utils.h"
#endif

std::unordered_set<std::string> findBagsCount (std::unordered_set<std::string>& uniqueBags, std::string bag, std::map<std::string, std::vector<std::string>>& bags) {

    for (auto& element : bags) {
        for (auto& str : element.second) {
            if (str == bag) {
                std::cout << "FOUND IN " << element.first << "\n";
                uniqueBags.insert(element.first);
                findBagsCount(uniqueBags, element.first, bags);
            }
        }
    }

    return uniqueBags;
}

int Solver::Solve_day_7_part1() {

    std::string line;
    std::regex container_regex("([0-9]+)([a-z ]+)");
    std::map<std::string, std::vector<std::string>> bags;

    while (std::getline(file, line)) {
        size_t index = line.find(" contain ");
        std::string container_bag = line.substr(0, index);
        std::smatch matches;
        line.erase(0, index + 9);

        std::vector<std::string> containedBags;
        std::string tmp;
        while (true) {
            index = line.find(',');
            std::regex_search(line, matches, container_regex);
            if (matches.size() >= 1) {
                size_t indexTmp = matches[2].str().find(" bag") - 1;
                tmp = matches[2].str().substr(1,indexTmp);
                // std::cout << tmp << std::endl;
                containedBags.push_back(tmp);
            }
            line.erase(0, index + 1);
            if (index == std::string::npos) {
                break;
            }
        }
        index = container_bag.find("bags") - 1;
        container_bag = container_bag.substr(0, index);
        bags.emplace(container_bag, containedBags);
    }

    // Recursive search through containers to find all combinations of bags having a shiny gold bag.
    std::unordered_set<std::string> bagsList;
    bagsList = findBagsCount(bagsList, "shiny gold", bags);
    return bagsList.size();
}

#endif  // DAY7_H
