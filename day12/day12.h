#ifndef DAY12_H
#define DAY12_H

#ifndef UTILS_H
#include "../utils.h"
#endif

int Solver::Solve_day_12_part1() {
  std::string line;
  char direction;
  int movement;
  int x = 0;
  int y = 0;
  int rotation = 0;

  while (std::getline(file, line)) {
    direction = line[0];
    line.erase(0, 1);
    movement = std::stoi(line);
    std::cout << movement << " " << direction << std::endl;

    switch (direction) {
      case 'N':
        y += movement;
        break;
      case 'S':
        y -= movement;
        break;
      case 'E':
        x += movement;
        break;
      case 'W':
        x -= movement;
        break;
      case 'L':
        rotation = (rotation - movement + 360) % 360;
        break;
      case 'R':
        rotation = (rotation + movement) % 360;
        break;
      case 'F':
        switch (rotation) {
          case 0:
            x += movement;
            break;
          case 90:
            y -= movement;
            break;
          case 180:
            x -= movement;
            break;
          case 270:
            y += movement;
            break;
        }
        break;
      default:
        break;
    }
  }
  return std::abs(x) + std::abs(y);
}

#endif
