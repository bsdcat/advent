#include <cstdio>
#include <fstream>
#include <list>
#include <string>

const int memory = 25;

int main(int argc, char *argv[]) {
  std::ifstream input = std::ifstream("day-9-input.txt");
  if (!input.is_open())
    return 1;

  std::list<uint64_t> valid_numbers;

  char line[256] = {0};
  while (input.getline(line, 256)) {
    std::string linestr(line);
    int64_t val = std::stoll(linestr);
    if (valid_numbers.size() == memory) {
      bool found = false;
      for (auto it = valid_numbers.begin(); it != valid_numbers.end(); ++it) {
        auto jt = it;
        ++jt;
        for (; jt != valid_numbers.end(); ++jt) {
          if (*it + *jt == val) {
            found = true;
            break;
          }
        }
        if (found)
          break;
      }
      if (!found) {
        printf("%lld is not a valid sum of the previous %d values\n", val, memory);
        break;
      } else {
        valid_numbers.pop_front();
      }
    }
    valid_numbers.push_back(val);
  }

  return 0;
}
