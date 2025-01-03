#ifndef DAY12_2020_H
#define DAY12_2020_H

#ifndef UTILS_2020_H
#include "utils2020.h"
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

struct Ship {
  int x = 0;
  int y = 0;
};

struct Waypoint {
  int x = 0;
  int y = 0;
};

int Solver::Solve_day_12_part2() {
  std::string line;
  char direction;
  int movement;

  struct Ship {
    int x = 0;
    int y = 0;
  } ship;

  struct Waypoint {
    int x = 10;
    int y = 1;
  } waypoint;

  while (std::getline(file, line)) {
    direction = line[0];
    movement = std::stoi(line.substr(1));

    switch (direction) {
      case 'N':
        waypoint.y += movement;
        break;
      case 'S':
        waypoint.y -= movement;
        break;
      case 'E':
        waypoint.x += movement;
        break;
      case 'W':
        waypoint.x -= movement;
        break;
      case 'L': // Rotate counterclockwise
        for (int i = 0; i < movement / 90; ++i) {
          int tempX = waypoint.x;
          waypoint.x = -waypoint.y;
          waypoint.y = tempX;
        }
        break;
      case 'R': // Rotate clockwise
        for (int i = 0; i < movement / 90; ++i) {
          int tempX = waypoint.x;
          waypoint.x = waypoint.y;
          waypoint.y = -tempX;
        }
        break;
      case 'F': // Move ship towards waypoint
        ship.x += movement * waypoint.x;
        ship.y += movement * waypoint.y;
        break;
    }
  }

  // Manhattan distance from the origin
  return std::abs(ship.x) + std::abs(ship.y);
}

#endif
