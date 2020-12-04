#include <cstdio>
#include <cstring>

int main(int argc, char *argv[]) {
  FILE *input = fopen("day-2-input.txt", "r");
  if (!input) return 1;

  int valid = 0;
  int min, max;
  char req_char;
  char password[129];
  while (fscanf(input, "%d-%d %c: %s", &min, &max, &req_char, password) == 4) {
    int count = 0;
    int len = strnlen(password, 128);
    for (int i = 0; i < len; ++i) {
      if (password[i] == req_char) count++;
    }
    if (count >= min && count <= max) {
      valid++;
    }
  }

  printf("Valid count is %d\n", valid);

  return 0;
}
