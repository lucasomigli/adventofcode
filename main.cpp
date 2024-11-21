#include "day15/day15.h"
int main() {
  std::cout << "Using version " << __cplusplus << std::endl;

  std::string AOC_day = "day15";
  std::cout << "AdventOfCode Solution for: " << AOC_day << std::endl;
  std::filesystem::path currentPath = std::filesystem::current_path();

  std::string solutionPath = currentPath.generic_string() + "/" + AOC_day;
  std::string inputFile = solutionPath + "/input.txt";
  std::string testFile = solutionPath + "/test.txt";

  std::cout << solutionPath << std::endl;
  Solver solver("/Users/luca/eclipse/eclipse-workspace/adventofcode/src/day15/input.txt");
  int solution = solver.Solve_day_15(30000000);
  std::cout << "The Solution is: " << solution << std::endl;

  return 0;
}
