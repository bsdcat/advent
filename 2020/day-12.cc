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

  return 0;
}
