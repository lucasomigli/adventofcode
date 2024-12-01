#ifndef DAY07_2020_H
#define DAY07_2020_H

#ifndef UTILS_2020_H
#include "../utils2020.h"
#endif

inline long findNumberOfBags(const long &uniqueBagsCount, const std::string &bag,
                             std::map<std::string, std::vector<std::pair<std::string, int> > > &bags) {
    long count = uniqueBagsCount;
    if (bags[bag].empty()) {
        return 1;
    }
    for (auto &containedBag: bags[bag]) {
        count += findNumberOfBags(uniqueBagsCount, containedBag.first, bags) * containedBag.second;
    }
    std::cout << bag << " TotalCount: " << count << std::endl;
    return count + 1;
}

inline long Solver::Solve_day_7_part2() {
    std::string line;
    std::regex container_regex("([0-9]+)([a-z ]+)");
    std::map<std::string, std::vector<std::pair<std::string, int> > > bags;

    while (std::getline(file, line)) {
        size_t index = line.find(" contain ");
        std::string container_bag = line.substr(0, index);
        std::smatch matches;
        line.erase(0, index + 9);

        std::vector<std::pair<std::string, int> > containedBags;
        std::string tmp;
        while (true) {
            index = line.find(',');
            std::regex_search(line, matches, container_regex);
            if (!matches.empty()) {
                std::pair<std::string, int> containedBag;
                size_t indexTmp = matches[2].str().find(" bag") - 1;
                tmp = matches[2].str().substr(1, indexTmp);
                containedBag = std::make_pair(tmp, std::stoi(matches[1].str()));
                containedBags.push_back(containedBag);
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
    long bagsList = findNumberOfBags(0, "shiny gold", bags);

    return bagsList - 1;
}

inline std::unordered_set<std::string> findBagsCount(std::unordered_set<std::string> &uniqueBags,
                                                     const std::string &bag,
                                                     std::map<std::string, std::vector<std::string> > &bags) {
    for (auto &element: bags) {
        for (auto &str: element.second) {
            if (str == bag) {
                uniqueBags.insert(element.first);
                findBagsCount(uniqueBags, element.first, bags);
            }
        }
    }

    return uniqueBags;
}

inline long Solver::Solve_day_7_part1() {
    std::string line;
    std::regex container_regex("([0-9]+)([a-z ]+)");
    std::map<std::string, std::vector<std::string> > bags;

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
            if (!matches.empty()) {
                size_t indexTmp = matches[2].str().find(" bag") - 1;
                tmp = matches[2].str().substr(1, indexTmp);
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
    return static_cast<long>(bagsList.size());
}

#endif
