#include <cstdio>
#include <cstdlib>
#include <string>

int main(int argc, char *argv[]) {
  FILE *input = fopen("day-5-input.txt", "r");
  if (!input) return 1;

  unsigned char assignments[128] = {0};

  char seat_id[11] = {0};
  int max_assignment = 0;
  while (fscanf(input, "%s", seat_id) == 1) {
    int row = 0;
    for (int i = 0; i < 7; ++i) {
      row = row << 1;
      if (seat_id[i] == 'B')
        row += 1;
    }
    int seat = 0;
    for (int i = 7; i < 10; ++i) {
      seat = seat << 1;
      if (seat_id[i] == 'R')
        seat += 1;
    }

    assignments[row] = assignments[row] | (1 << seat);

    if (max_assignment < row * 8 + seat)
      max_assignment = row * 8 + seat;
  }

  int my_assignment = 0;
  for (int i = 1; i < 127; ++i) {
    if (assignments[i] < 255) {
      for (int j = 0; j < 8; ++j) {
        if ((assignments[i] & (1 << j)) == 0) {
          if (j == 0 && (assignments[i-1] & (1 << 7)) == 0)
            continue;
          if (j == 7 && (assignments[i+1] & 1) == 0)
            continue;
          if ((assignments[i] & (1 << (j-1))) == 0 || (assignments[i] & (1 << (j+1))) == 0)
            continue;
          my_assignment = i * 8 + j;
          i = 128;
          j = 8;
        }
      }
    }
  }

  printf("my assignment is %d\n", my_assignment);
  printf("max assignment is %d\n", max_assignment);

  return 0;
}
