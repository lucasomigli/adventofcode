#include "adventofcode2024/day14.h"

int main() {
    std::cout << "Using C++ version " << __cplusplus << std::endl;
    std::string INPUTFILE = std::filesystem::current_path().generic_string() + "/input.txt";

    Solver solver(INPUTFILE);
    long solution = solver.Solve_Day14_part2();
    std::cout << "The Solution is: " << solution << std::endl;

    return 0;
}