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
  int rotation = 0;

  Ship ship;
  Waypoint waypoint;
  waypoint.x = ship.x + 10;
  waypoint.y = ship.y + 1;

  while (std::getline(file, line)) {
    direction = line[0];
    line.erase(0, 1);
    movement = std::stoi(line);
    std::cout << movement << " " << direction << std::endl;

    switch (direction) {
      case 'N':
        waypoint.y += direction;
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
      case 'L':
        rotation = (rotation - movement + 360) % 360;
        break;
      case 'R':
        rotation = (rotation + movement) % 360;
        break;
      case 'F':
        int distanceX = waypoint.x - ship.x;
        int distanceY = waypoint.y - ship.y;
        //        std::cout << "DEBUG" << movement * (waypoint.x - ship.x) <<
        //        std::endl;
        ship.x += movement * (waypoint.x - ship.x);
        ship.y += movement * (waypoint.y - ship.y);
        waypoint.x = ship.x + distanceX;
        waypoint.y = ship.y + distanceY;
        break;
    }

    std::cout << "Direction: " << direction << " Movement: " << movement
              << " ship.x: " << ship.x << " ship.y: " << ship.y
              << " waypoint.x: " << waypoint.x << " waypoint.y: " << waypoint.y
              << std::endl;
  }
  return 1;
}

#endif
