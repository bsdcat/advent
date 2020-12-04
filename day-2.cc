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
    bool just_one = false;
    if (min <= len)
      if (password[min - 1] == req_char)
        just_one = !just_one;
    if (max <= len)
      if (password[max - 1] == req_char)
        just_one = !just_one;

    if (just_one) {
      printf("%d-%d %c: %s - ", min, max, req_char, password);
      printf("%c, %c\n", password[min - 1], password[max - 1]);
      valid++;
    }
  }

  printf("Valid count is %d\n", valid);

  return 0;
}
