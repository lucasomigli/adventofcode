#ifndef DAY14_H
#define DAY14_H

#ifndef UTILS_H
#include "../utils.h"
#endif

#include <bitset>

unsigned long long bitMapTransform(const long& value, const std::string& mask) {
  std::string binary = std::bitset<36>(value).to_string();  // to binary
  std::string out = mask;
  for (size_t i = 0; i < binary.size(); ++i) {
    if (mask[i] == 'X') {
      out[i] = binary[i];
    }
  }
  std::bitset<36> transformed = std::bitset<36>(out);
  long l = transformed.to_ulong();
  //  std::cout << value << " -> " << out << " -> " << l << std::endl;
  return l;
}

int Solver::Solve_day_14_part1() {
  std::string line;
  std::stringstream ss;
  std::string key;
  std::string value;
  std::string mask;
  int k = 0;
  long v = 0;
  std::map<int, unsigned long long> mem;

  while (std::getline(file, line)) {
    ss << line;
    std::getline(ss, key, '=');
    std::getline(ss, value, '=');

    if (key.contains("mask")) {
      value = value.substr(1, 36);
      mask = value;
    } else {
      size_t start = key.find('[') + 1;
      size_t end = key.find(']');
      key = key.substr(start, end);
      k = std::stoi(key);
      v = std::stol(value);
      unsigned long long transformedValue = bitMapTransform(v, mask);
      mem[k] = transformedValue;
    }

    ss.clear();
  }

  std::map<int, unsigned long long>::iterator it;
  unsigned long long count = 0;
  for (it = mem.begin(); it != mem.end(); it++) {
    count += it->second;
  }

  std::cout << "Final count in memory: " << count << std::endl;
  return count;
}

#endif
