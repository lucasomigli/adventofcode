#include "day17/day17.h"

int main() {
  std::cout << "Using version " << __cplusplus << std::endl;

  std::string AOC_day = "day17";
  std::cout << "AdventOfCode Solution for: " << AOC_day << std::endl;
  std::filesystem::path currentPath = std::filesystem::current_path();

  std::string solutionPath = currentPath.generic_string() + "/../" + AOC_day;
  std::string inputFile = solutionPath + "/input.txt";
  std::string testFile = solutionPath + "/test.txt";
  std::string used = inputFile; // change this to use either the input.txt or test.txt file
  std::cout << "Input file: " << used << std::endl;
  Solver solver(testFile);
  int solution = solver.Solve_day_17_part1();
  std::cout << "The Solution is: " << solution << std::endl;

  return 0;
}
