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

typedef int counting_function(const seating_map &a_map, int i, int j);

void print_map(const seating_map &a_map) {
  for (const std::string &line : a_map)
    printf("%s\n", line.c_str());
  printf("\n");
}

bool equals(const seating_map &map1, const seating_map &map2) {
  if (map1.size() != map2.size())
    return false;
  for (int i = 0; i < map1.size(); ++i) {
    if (map1[i] != map2[i])
      return false;
  }
  return true;
}

bool count_seat_adj_helper(const seating_map &a_map, int i, int j) {
  if (i >= 0 && i < a_map.size())
    if (j >= 0 && j < a_map[i].length())
      if (a_map[i][j] == spot::OCCUPIED)
        return true;
  return false;
}

int count_seat_adj(const seating_map &a_map, int i, int j) {
  int adjacent_count = 0;
  for (int ip = i - 1; ip <= i + 1; ++ip) {
    for (int jp = j - 1; jp <= j + 1; ++jp) {
      if (ip == i && jp == j)
        continue;
      if (count_seat_adj_helper(a_map, ip, jp))
        adjacent_count++;
    }
  }
  return adjacent_count;
}

bool count_seat_los_helper(const seating_map &a_map, int i, int j, int di, int dj) {
  int i_step = di;
  int j_step = dj;
  while (i + di >= 0 && i + di < a_map.size()
         && j + dj >= 0 && j + dj < a_map[i + di].length()) {
    switch(a_map[i + di][j + dj]) {
    case spot::FLOOR:
      di += i_step;
      dj += j_step;
      break;
    case spot::OCCUPIED:
      return true;
    case spot::EMPTY:
      return false;
    }    
  }
  return false;
}

int count_seat_los(const seating_map &a_map, int i, int j) {
  int adjacent_count = 0;
  for (int di = -1; di <= 1; ++di) {
    for (int dj = -1; dj <= 1; ++dj) {
      if (di == 0 && dj == 0)
        continue;
      if (count_seat_los_helper(a_map, i, j, di, dj))
        adjacent_count++;
    }
  }
  return adjacent_count;
}

void permute_map(seating_map &map1, seating_map &map2, const int adjacency, counting_function *fn) {
  for (int i = 0; i < map1.size(); ++i) {
    for (int j = 0; j < map1[i].length(); ++j) {
      int adjacent_count = fn(map1, i, j);

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
        if (adjacent_count >= adjacency)
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

  seating_map map1(a_map);
  seating_map map2(a_map);
  do {
    permute_map(map1, map2, 4, &count_seat_adj);
    std::swap(map1, map2);
  } while (!equals(map1, map2));

  seating_map map3(a_map);
  seating_map map4(a_map);

  do {
    permute_map(map3, map4, 5, &count_seat_los);
    std::swap(map3, map4);
  } while (!equals(map3, map4));

  int occupied_seats = 0;
  for (int i = 0; i < map1.size(); ++i) {
    for (int j = 0; j < map1[i].length(); ++j) {
      if (map1[i][j] == spot::OCCUPIED)
        occupied_seats++;
    }
  }
  printf("There are %d occupied seats with adjacency count of 4.\n", occupied_seats);

  occupied_seats = 0;
  for (int i = 0; i < map3.size(); ++i) {
    for (int j = 0; j < map3[i].length(); ++j) {
      if (map3[i][j] == spot::OCCUPIED)
        occupied_seats++;
    }
  }
  printf("There are %d occupied seats with LOS count of 5.\n", occupied_seats);

  return 0;
}
