#include "adventofcode2024/day06/day06.h"

int main() {
    std::cout << "Using version " << __cplusplus << std::endl;

    std::string AOC_day = R"(adventofcode2024/day06)";
    std::cout << "AdventOfCode Solution for: " << AOC_day << std::endl;
    std::filesystem::path currentPath = std::filesystem::current_path();

    std::string solutionPath = currentPath.generic_string() + "/src/" + AOC_day;
    std::string inputFile = solutionPath + "/input.txt";
    std::string testFile = solutionPath + "/test.txt";

    std::string used = testFile;  // change this to use either the input.txt or test.txt file
    std::cout << "Input file: " << used << std::endl;

    Solver solver(used);
    long solution = solver.Solve_Day06_part1();
    std::cout << "The Solution is: " << solution << std::endl;

    return 0;
}
