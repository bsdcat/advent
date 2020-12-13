#include <cmath>
#include <cstdio>
#include <fstream>
#include <list>
#include <string>
#include <utility>
#include <vector>

enum heading {
  E = 0,
  S,
  W,
  N,
  HEADING_MAX,
};

enum heading_change {
  R = 1,
  L = 3, // -1 modulo 4
};

void rotate_right(int &x, int &y) {
  int new_x = y;
  y = -x;
  x = new_x;
}

void rotate_left(int &x, int &y) {
  int new_y = x;
  x = -y;
  y = new_y;
}

void flip_back(int &x, int &y) {
  x = -x;
  y = -y;
}

int main(int argc, char *argv[]) {
  std::ifstream input = std::ifstream("day-12-input.txt");
  if (!input.is_open())
    return 1;

  std::vector<std::string> instructions;
  int x = 0;
  int y = 0;
  int facing = heading::E;
  char line[256];
  while (input.getline(line, 256)) {
    instructions.push_back(line);
    char instr = line[0];
    int val = atoi(line + 1);
    switch (instr) {
    case 'F':
      switch (facing) {
      case heading::E:
        x += val;
        break;
      case heading::S:
        y -= val;
        break;
      case heading::W:
        x -= val;
        break;
      case heading::N:
        y += val;
        break;
      default:
        printf("doh %d\n", facing);
        exit(2);
      }
      break;
    case 'E':
      x += val;
      break;
    case 'W':
      x -= val;
      break;
    case 'N':
      y += val;
      break;
    case 'S':
      y -= val;
      break;
    case 'L':
      facing = (facing + heading_change::L * (val / 90)) % heading::HEADING_MAX;
      printf("facing change: %s resulting in %d\n", line, facing);
      break;
    case 'R':
      facing = (facing + heading_change::R * (val / 90)) % heading::HEADING_MAX;
      printf("facing change: %s resulting in %d\n", line, facing);
      break;
    default:
      printf("ope\n");
      exit(1);
    }
  }

  printf("result is %u east/west and %u north/south\n", abs(x), abs(y));
  printf("Manhattan distance is %u\n", abs(x) + abs(y));

  x = 0;
  y = 0;
  int wx = 10;
  int wy = 1;

  for (std::string &line : instructions) {
    int val = std::stoi(line.substr(1));
    switch (line[0]) {
    case 'F':
      x += val * wx;
      y += val * wy;
      break;
    case 'E':
      wx += val;
      break;
    case 'W':
      wx -= val;
      break;
    case 'N':
      wy += val;
      break;
    case 'S':
      wy -= val;
      break;
    case 'L':
      switch (val) {
      case 90:
        rotate_left(wx, wy);
        break;
      case 180:
        flip_back(wx, wy);
        break;
      case 270:
        rotate_right(wx, wy);
        break;
      default:
        printf("shoot\n");
        exit(5);
      }
      break;
    case 'R':
      switch (val) {
      case 90:
        rotate_right(wx, wy);
        break;
      case 180:
        flip_back(wx, wy);
        break;
      case 270:
        rotate_left(wx, wy);
        break;
      default:
        printf("oof\n");
        exit(4);
      }
      break;
    default:
      printf("dang %c\n", line[0]);
      exit(3);
    }
  }

  printf("REAL result is %u east/west and %u north/south\n", abs(x), abs(y));
  printf("REAL Manhattan distance is %u\n", abs(x) + abs(y));

  return 0;
}
