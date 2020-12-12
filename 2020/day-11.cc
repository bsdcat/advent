#include <algorithm>
#include <cstdio>
#include <fstream>
#include <set>
#include <string>
#include <vector>

enum spot {
  FLOOR = '.',
  EMPTY = 'L',
  OCCUPIED = '#',
};

typedef std::vector<std::string> seating_map;

bool equals(const seating_map &map1, const seating_map &map2) {
  if (map1.size() != map2.size())
    return false;
  for (int i = 0; i < map1.size(); ++i) {
    if (map1[i] != map2[i])
      return false;
  }
  return true;
}

bool count_seat(const seating_map &a_map, int i, int j) {
  if (i >= 0 && i < a_map.size())
    if (j >= 0 && j < a_map[i].length())
      if (a_map[i][j] == spot::OCCUPIED)
        return true;
  return false;
}

void permute_map(seating_map &map1, seating_map &map2) {
  for (int i = 0; i < map1.size(); ++i) {
    for (int j = 0; j < map1[i].length(); ++j) {
      int adjacent_count = 0;
      for (int ip = i - 1; ip <= i + 1; ++ip) {
        for (int jp = j - 1; jp <= j + 1; ++jp) {
          if (ip == i && jp == j)
            continue;
          if (count_seat(map1, ip, jp))
            adjacent_count++;
        }
      }

      switch (map1[i][j]) {
      case spot::FLOOR:
        map2[i][j] = spot::FLOOR;
        break;
      case spot::EMPTY:
        if (adjacent_count == 0)
          map2[i][j] = spot::OCCUPIED;
        else
          map2[i][j] = spot::EMPTY;
        break;
      case spot::OCCUPIED:
        if (adjacent_count >= 4)
          map2[i][j] = spot::EMPTY;
        else
          map2[i][j] = spot::OCCUPIED;
        break;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  std::ifstream input = std::ifstream("day-11-input.txt");
  if (!input.is_open())
    return 1;

  seating_map a_map;

  char line[256];
  while (input.getline(line, 256)) {
    std::string linestr(line);
    a_map.push_back(linestr);
  }

  seating_map next_map(a_map);
  do {
    permute_map(a_map, next_map);
    std::swap(a_map, next_map);
  } while (!equals(a_map, next_map));

  printf("now they're equal\n");

  int occupied_seats = 0;
  for (int i = 0; i < a_map.size(); ++i) {
    for (int j = 0; j < a_map[i].length(); ++j) {
      if (a_map[i][j] == spot::OCCUPIED)
        occupied_seats++;
    }
  }

  printf("There are %d occupied seats.\n", occupied_seats);

  return 0;
}
