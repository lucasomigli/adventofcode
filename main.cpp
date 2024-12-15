#include "adventofcode2024/day12.h"

int main() {
    std::cout << "Using C++ version " << __cplusplus << std::endl;
    std::filesystem::current_path();
    std::string INPUTFILE = std::filesystem::current_path().generic_string() + "/input.txt";

    Solver solver(INPUTFILE);
    long solution = solver.Solve_Day12_part1();
    std::cout << "The Solution is: " << solution << std::endl;

    return 0;
}
