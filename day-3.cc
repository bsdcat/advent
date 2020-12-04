#include <cstdio>
#include <cstdlib>
#include <cstring>

int64_t trees_for_angle(int **rows, int right, int down) {
  int64_t trees = 0;
  int pos = 0;
  for (int i = down; i < 323; i += down) {
    pos = (pos + right) % 31;
    if (rows[i][pos] == '#') {
      trees++;
    }
  }
  return trees;
}

int main(int argc, char *argv[]) {
  FILE *input = fopen("day-3-input.txt", "r");
  if (!input) return 1;

  int *rows[323];
  for (int i = 0; i < 323; i++) {
    rows[i] = static_cast<int *>(malloc(sizeof(int)* 31));
  }

  for (int i = 0; i < 323; i++) {
    for (int j = 0; j < 31; j++) {
      rows[i][j] = fgetc(input);
    }
    fgetc(input);
  }

  printf("trees = %lld\n",
         trees_for_angle(rows, 1, 1) *
         trees_for_angle(rows, 3, 1) *
         trees_for_angle(rows, 5, 1) *
         trees_for_angle(rows, 7, 1) *
         trees_for_angle(rows, 1, 2));
  

  return 0;
}
