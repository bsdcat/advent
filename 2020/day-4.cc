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
  int count_1 = 0;
  int count_2 = 0;
  while (!eof) {
    bool hgt_1 = false;
    bool iyr_1 = false;
    bool ecl_1 = false;
    bool eyr_1 = false;
    bool byr_1 = false;
    bool hcl_1 = false;
    bool pid_1 = false;
    bool cid_1 = false;
    bool valid_1 = false;
    bool hgt_2 = false;
    bool iyr_2 = false;
    bool ecl_2 = false;
    bool eyr_2 = false;
    bool byr_2 = false;
    bool hcl_2 = false;
    bool pid_2 = false;
    bool cid_2 = false;
    bool valid_2 = false;

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

        if (key == "hgt") {
          hgt_1 = true;
          hgt_2 = valid_hgt(value);
        }
        if (key == "iyr") {
          iyr_1 = true;
          iyr_2 = valid_iyr(value);
        }
        if (key == "ecl") {
          ecl_1 = true;
          ecl_2 = valid_ecl(value);
        }
        if (key == "eyr") {
          eyr_1 = true;
          eyr_2 = valid_eyr(value);
        }
        if (key == "byr") {
          byr_1 = true;
          byr_2 = valid_byr(value);
        }
        if (key == "hcl") {
          hcl_1 = true;
          hcl_2 = valid_hcl(value);
        }
        if (key == "pid") {
          pid_1 = true;
          pid_2 = valid_pid(value);
        }
        if (key == "cid") {
          cid_1 = true;
          cid_2 = true;
          printf("cid:%s ", value.c_str());
        }
      }

      if (hgt_1 && iyr_1 && ecl_1 && eyr_1 && byr_1 && hcl_1 && pid_1) {
        if (!valid_1)
          count_1++;
        valid_1 = true;
      }

      if (hgt_2 && iyr_2 && ecl_2 && eyr_2 && byr_2 && hcl_2 && pid_2) {
        if (!valid_2)
          count_2++;
        valid_2 = true;
        printf("valid");
      }
    }
  }

  printf("passports with enough fields = %d\n", count_1);
  printf("valid passports = %d\n", count_2);

  return 0;
}
