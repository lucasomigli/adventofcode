#include "day13/day13.h"

int main() {
  std::cout << "Using version " << __cplusplus << std::endl;

  std::string AOC_day = "day13";
  std::cout << "AdventOfCode Solution for: " << AOC_day << std::endl;
  std::filesystem::path currentPath = std::filesystem::current_path();

  std::string solutionPath = currentPath.generic_string() + "/" + AOC_day;
  std::string inputFile = solutionPath + "/input.txt";
  std::string testFile = solutionPath + "/test.txt";

  Solver solver(inputFile);
  int solution = solver.Solve_day_13_part2();
  std::cout << "The Solution is: " << solution << std::endl;

  return 0;
}
