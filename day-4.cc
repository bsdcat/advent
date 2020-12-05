#include <cstdio>
#include <cstdlib>
#include <set>
#include <string>

bool valid_byr(char *value) {
  printf("byr:%s ", value);
  int byr = atoi(value);
  if (byr < 1920 || byr > 2002)
    return false;
  return true;
}

bool valid_iyr(char *value) {
  printf("iyr:%s ", value);
  int iyr = atoi(value);
  if (iyr < 2010 || iyr > 2020)
    return false;
  return true;
}

bool valid_eyr(char *value) {
  printf("eyr:%s ", value);
  int eyr = atoi(value);
  if (eyr < 2020 || eyr > 2030)
    return false;
  return true;
}

bool valid_hgt(char *value) {
  printf("hgt:%s ", value);
  size_t len = strlen(value);
  int height = atoi(value);
  if (value[len-2] == 'c' && value[len-1] == 'm' && height >= 150 && height <= 193)
    return true;
  if (value[len-2] == 'i' && value[len-1] == 'n' && height >= 59 && height <= 76)
    return true;
  return false;
}

bool valid_hcl(char *value) {
  printf("hcl:%s ", value);
  if (strlen(value) != 7)
    return false;
  if (value[0] != '#')
    return false;
  for (int i = 1; i < 7; i++) {
    if (value[i] < '0' || (value[i] > '9' && value[i] < 'a') || value[i] > 'f')
      return false;
  }
  return true;
}

bool valid_ecl(char *value) {
  printf("ecl:%s ", value);
  if (strcmp(value, "amb") == 0 ||
      strcmp(value, "blu") == 0 ||
      strcmp(value, "brn") == 0 ||
      strcmp(value, "gry") == 0 ||
      strcmp(value, "grn") == 0 ||
      strcmp(value, "hzl") == 0 ||
      strcmp(value, "oth") == 0)
    return true;
  return false;
}

bool valid_pid(char *value) {
  printf("pid:%s ", value);
  if (strlen(value) != 9)
    return false;
  for (int i = 0; i < 9; i++) {
    if (value[i] < '0' || value[i] > '9')
      return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  FILE *input = fopen("day-4-input.txt", "r");
  if (!input) return 1;

  char line[256];
  bool eof = false;
  int count = 0;
  while (!eof) {
    bool hgt = false;
    bool iyr = false;
    bool ecl = false;
    bool eyr = false;
    bool byr = false;
    bool hcl = false;
    bool pid = false;
    bool cid = false;
    bool valid = false;

    while (true) {
      for (int i = 0; i < 256; ++i) {
        line[i] = fgetc(input);
        if (line[i] == EOF) {
          eof = true;
          break;
        }
        if (isspace(line[i]))
          break;
      }
      if (eof || line[0] == '\n') {
        printf("\n");
        break;
      }
      
      line[255] = '\0';
      char key[32] = {0};
      char value[32] = {0};
      if (sscanf(line, "%s:%s", key, value) > 0) {
        size_t offset = strcspn(key, ":");
        key[offset] = '\0';
        strcpy(value, key + offset + 1);
        //printf("KEY: '%s' VALUE: '%s' ", key, value);

        if (strcmp(key, "hgt") == 0)
          hgt = valid_hgt(value);
        if (strcmp(key, "iyr") == 0)
          iyr = valid_iyr(value);
        if (strcmp(key, "ecl") == 0)
          ecl = valid_ecl(value);
        if (strcmp(key, "eyr") == 0)
          eyr = valid_eyr(value);
        if (strcmp(key, "byr") == 0)
          byr = valid_byr(value);
        if (strcmp(key, "hcl") == 0)
          hcl = valid_hcl(value);
        if (strcmp(key, "pid") == 0)
          pid = valid_pid(value);
        if (strcmp(key, "cid") == 0) {
          cid = true;
          printf("cid:%s ", value);
        }
      }

      if (hgt && iyr && ecl && eyr && byr && hcl && pid) {
        if (!valid)
          count++;
        valid = true;
        printf("valid");
      }
    }
  }

  printf("valid passports = %d\n", count);

  return 0;
}
