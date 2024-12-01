#ifndef DAY14_2020_H
#define DAY14_2020_H

#ifndef UTILS_2020_H
#include "../utils2020.h"
#endif

#include <bitset>
#include <cmath>

long long bitMapTransform(const long &value, const std::string &mask) {
  std::string binary = std::bitset<36>(value).to_string(); // to binary
  std::string out = mask;
  for (size_t i = 0; i < binary.size(); ++i) {
    if (mask[i] == 'X') {
      out[i] = binary[i];
    }
  }
  std::bitset<36> transformed = std::bitset<36>(out);
  long l = transformed.to_ulong();
  return l;
}

long Solver::Solve_day_14_part1() {
  std::string line;
  std::stringstream ss;
  std::string key;
  std::string value;
  std::string mask;
  int k = 0;
  long v = 0;
  std::map<int, long long> mem;

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
      key = key.substr(start, end - start);
      k = std::stoi(key);
      v = std::stol(value);
      long long transformedValue = bitMapTransform(v, mask);
      mem[k] = transformedValue;
    }

    ss.clear();
  }

  std::map<int, long long>::iterator it;
  long long count = 0;
  for (it = mem.begin(); it != mem.end(); it++) {
    count += it->second;
  }

  std::cout << "Final count in memory: " << count << std::endl;
  return count;
}

// PART 2 // //
// // // // //
// // // // //

std::vector<std::vector<char> > generateBinaryCombinations(int n) {
  std::vector<std::vector<char> > combinations;
  long totalCombinations =
      std::pow(2, n); // Total number of combinations = 2^n
  for (long i = 0; i < totalCombinations; ++i) {
    std::vector<char> combination;
    char tmp;

    for (int bit = n - 1; bit >= 0; --bit) {
      // Extract each bit and convert it to '0' or '1'
      tmp = ((i >> bit) & 1) ? '1' : '0';
      combination.push_back(tmp);
    }
    combinations.push_back(combination);
  }

  return combinations;
}

std::vector<long long> bitMapTransformMemDecoder(long long &address,
                                                 const std::string &mask) {
  std::string binary = std::bitset<36>(address).to_string(); // to binary
  std::string out = mask;

  // transform to floating point address
  std::vector<int> x_pos;
  for (size_t i = 0; i < binary.size(); ++i) {
    if (mask[i] == '0') {
      out[i] = binary[i];
    } else if (mask[i] == '1') {
      out[i] = '1';
    } else if (mask[i] == 'X') {
      out[i] = 'X';
      x_pos.push_back(i);
    }
  }

  // get vector of addresses with all possible permutations of floating points
  std::vector<long long> permutatedAddresses;
  std::vector<std::vector<char> > combs =
      generateBinaryCombinations(x_pos.size());
  std::bitset<36> transformed;

  for (auto combination: combs) {
    for (size_t i = 0; i < x_pos.size(); ++i) {
      out[x_pos[i]] = combination[i];
    }

    transformed = std::bitset<36>(out);
    permutatedAddresses.push_back(transformed.to_ulong());
  }

  return permutatedAddresses;
}

long long Solver::Solve_day_14_part2() {
  std::string line;
  std::stringstream ss;
  std::string key;
  std::string value;
  std::string mask;
  long long address = 0;
  long long valueToWrite = 0;
  std::map<long long, long long> mem;

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
      key = key.substr(start, end - start);
      address = std::stoll(key);

      // Get memory addresses via the decored function
      valueToWrite = std::stoll(value);
      std::vector<long long> memoryAddresses =
          bitMapTransformMemDecoder(address, mask);
      for (long long i: memoryAddresses) {
        mem[i] = valueToWrite;
      }
    }

    ss.clear();
  }

  std::map<long long, long long>::iterator it;
  long long count = 0;
  for (it = mem.begin(); it != mem.end(); it++) {
    count += it->second;
  }

  std::cout << "Final count in memory: " << count << std::endl;
  return count;
}

#endif
