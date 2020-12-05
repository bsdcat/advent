#include <cstdio>
#include <cstdlib>
#include <string>

int main(int argc, char *argv[]) {
  FILE *input = fopen("day-5-input.txt", "r");
  if (!input) return 1;

  char seat_id[11] = {0};
  int max_assignment = 0;
  while (fscanf(input, "%s", seat_id) == 1) {
    printf("%s\n", seat_id);
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

    if (max_assignment < row * 8 + seat)
      max_assignment = row * 8 + seat;
  }

  printf("max assignment is %d\n", max_assignment);

  return 0;
}
