#ifndef UTILS_H
#include "utils.h"
#endif

inline int findPassports(const std::string &fileName) {
  std::map<std::string, bool> keyStorage;

  std::fstream file;
  file.open(fileName);
  std::string line;

  int result = 0;
  int count = 0;
  int keyCount = 0;
  bool isValid;

  std::regex re_hcl("#[0-9a-f]{6}");
  std::regex re_pid("[0-9]{9}");
  std::regex re_hgt("(\\d+)(in|cm)");

  // find array of keys in line and return them in the map
  while (std::getline(file, line)) {
    std::stringstream stream(line);
    std::string segment;
    std::vector<std::string> seglist;

    while (std::getline(stream, segment, ' ')) {
      size_t foundKeySeparator = segment.find((char)':');
      if (foundKeySeparator != std::string::npos) {
        // : char found at position and insert key in keyStorage.
        std::stringstream seg(segment);
        std::string key;
        std::string value;

        std::getline(seg, key, ':');
        std::getline(seg, value, ':');

        isValid = false;

        if (key == "byr") {
          int v = std::stoi(value);
          if (1920 <= v && v <= 2002) {
            isValid = true;
            keyCount++;
          }
        } else if (key == "iyr") {
          int v = std::stoi(value);
          if (2010 <= v && v <= 2020) {
            isValid = true;
            keyCount++;
          }
        } else if (key == "eyr") {
          int v = std::stoi(value);
          if (2020 <= v && v <= 2030) {
            isValid = true;
            keyCount++;
          }
        } else if (key == "hgt") {
          isValid = std::regex_match(value, re_hgt);
          if (isValid) {
            std::smatch match;
            std::regex_search(value, match, re_hgt);
            int num = std::stoi(match[1].str());
            std::string unit = match[2].str();
            if ((unit == "cm" && num >= 150 && num <= 193) ||
                (unit == "in" && num >= 59 && num <= 76)) {
              isValid = true;
              keyCount++;
            }
          }
        } else if (key == "hcl") {
          isValid = std::regex_match(value, re_hcl);
          if (isValid) {
            keyCount++;
          };
        } else if (key == "ecl") {
          std::string allowed[7] = {"amb", "blu", "brn", "gry",
                                    "grn", "hzl", "oth"};
          for (auto st : allowed) {
            if (value == st) {
              isValid = true;
              keyCount++;
            }
          };
        } else if (key == "pid") {
          isValid = std::regex_match(value, re_pid);
          if (isValid) {
            keyCount++;
          };
        } else if (key == "cid") {
          isValid = true;
        };
      }
      if (!isValid || line.size() < 2) {
        break;
      };
    }

    if (!isValid) {
      while (line.size() > 2) {
        std::getline(file, line);
      }
      count += 1;
      keyCount = 0;
    } else if (isValid && line.size() < 2) {
      if (keyCount == 7) {
        result += 1;
      }
      count += 1;
      keyCount = 0;
    }
  }
  if (isValid) {
    result += 1;
    count += 1;
  }
  std::cout << "Final count is: " << count << std::endl;
  file.close();
  return result;
}
