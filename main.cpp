#include "adventofcode2024/day11/day11.h"

int main() {
    std::cout << "Using C++ version " << __cplusplus << std::endl;

    std::string AOC_day = R"(adventofcode2024/day11)";
    std::cout << "AdventOfCode Solution for: " << AOC_day << std::endl;

    // find path for current AOC day
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::regex re(".*" + AOC_day + "$");
    std::smatch sm;
    for (const auto& f : std::filesystem::directory_iterator(currentPath)) {
        if (f.is_directory()) {
            for (const auto& file : std::filesystem::directory_iterator(std::filesystem::path(f))) {
                std::string _path = file.path();
                if (std::regex_search(_path, sm, re)) {
                    currentPath = file.path();
                    break;
                }
            }
        }
    }

    std::string inputFile = currentPath.generic_string() + "/input.txt";
    std::string testFile = currentPath.generic_string() + "/test.txt";

    std::string used = "/Users/luca/eclipse/eclipse-workspace/adventofcode/src/adventofcode2024/day11/input.txt";  // change this to use either the input.txt or test.txt
    std::cout << "Input file: " << used << std::endl;

    Solver solver(used);
    long solution = solver.Solve_Day11_part1();
    std::cout << "The Solution is: " << solution << std::endl;

    return 0;
}
