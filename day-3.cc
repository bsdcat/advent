#include <cstdio>
#include <cstring>
#include <list>

int main(int argc, char *argv[]) {
  FILE *input = fopen("day-3-input.txt", "r");
  if (!input) return 1;

  int pos = 0;
  int c;
  int trees = 0;

  bool go_on = true;
  while (go_on) {
    printf("new pos is %d ", pos);
    for (int i = 0; i < 32; ++i) {
      c = fgetc(input);
      if (c == EOF) {
        go_on = false;
        break;
      }
      if (pos == i) {
        printf("%c\n", c);
        if (c == '#')
          trees++;
      }
    }
    pos = (pos + 3) % 31;
  }
  printf("trees = %d\n", trees);
  

  return 0;
}
