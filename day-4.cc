#include <cstdio>
#include <cstdlib>
#include <set>
#include <string>

bool valid_byr(const std::string &value) {
  printf("byr:%s ", value.c_str());
  int byr = std::stoi(value);
  if (byr < 1920 || byr > 2002)
    return false;
  return true;
}

bool valid_iyr(const std::string &value) {
  printf("iyr:%s ", value.c_str());
  int iyr = std::stoi(value);
  if (iyr < 2010 || iyr > 2020)
    return false;
  return true;
}

bool valid_eyr(const std::string &value) {
  printf("eyr:%s ", value.c_str());
  int eyr = std::stoi(value);
  if (eyr < 2020 || eyr > 2030)
    return false;
  return true;
}

bool valid_hgt(const std::string &value) {
  printf("hgt:%s ", value.c_str());
  size_t len = value.length();
  int height = std::stoi(value);
  if (value[len-2] == 'c' && value[len-1] == 'm' && height >= 150 && height <= 193)
    return true;
  if (value[len-2] == 'i' && value[len-1] == 'n' && height >= 59 && height <= 76)
    return true;
  return false;
}

bool valid_hcl(const std::string &value) {
  printf("hcl:%s ", value.c_str());
  if (value.length() != 7)
    return false;
  if (value[0] != '#')
    return false;
  for (int i = 1; i < 7; i++) {
    if (value[i] < '0' || (value[i] > '9' && value[i] < 'a') || value[i] > 'f')
      return false;
  }
  return true;
}

bool valid_ecl(const std::string &value) {
  printf("ecl:%s ", value.c_str());
  static std::set<std::string> colors = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
  return colors.find(value) != colors.end();
}

bool valid_pid(const std::string &value) {
  printf("pid:%s ", value.c_str());
  if (value.length() != 9)
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
      char entry[64] = {0};
      if (sscanf(line, "%s", entry) > 0) {
        size_t offset = strcspn(entry, ":");
        entry[offset] = '\0';
        std::string key = entry;
        std::string value = entry + offset + 1;

        if (key == "hgt")
          hgt = valid_hgt(value);
        if (key == "iyr")
          iyr = valid_iyr(value);
        if (key == "ecl")
          ecl = valid_ecl(value);
        if (key == "eyr")
          eyr = valid_eyr(value);
        if (key == "byr")
          byr = valid_byr(value);
        if (key == "hcl")
          hcl = valid_hcl(value);
        if (key == "pid")
          pid = valid_pid(value);
        if (key == "cid") {
          cid = true;
          printf("cid:%s ", value.c_str());
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
