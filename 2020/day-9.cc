#include <cstdio>
#include <fstream>
#include <limits>
#include <list>
#include <numeric>
#include <string>
#include <vector>

const int memory = 25;

int main(int argc, char *argv[]) {
  std::ifstream input = std::ifstream("day-9-input.txt");
  if (!input.is_open())
    return 1;

  std::list<int64_t> read_numbers;
  int distance = 0;

  int64_t key = 0;

  char line[256] = {0};
  while (input.getline(line, 256)) {
    std::string linestr(line);
    int64_t val = std::stoll(linestr);
    read_numbers.push_back(val);
  }
  
  std::vector<int64_t> valid_numbers(read_numbers.begin(), read_numbers.end());
  for (int i = memory; i < valid_numbers.size(); ++i) {
    bool found = false;
    for (int j = i - memory; j < i-1; ++j) {
      for (int k = j + 1; k < i; ++k) {
        if (valid_numbers[j] + valid_numbers[k] == valid_numbers[i]) {
          found = true;
          break;
        }
      }
      if (found)
        break;
    }
    if (!found) {
      printf("%lld is not a valid sum of the previous %d values\n", valid_numbers[i], memory);
      key = valid_numbers[i];
      break;
    }
  }

  for (int i = 0; i < valid_numbers.size() - 2; ++i) {
    bool found = false;
    for (int j = i + 2; j < valid_numbers.size(); ++j) {
      int64_t current_sum = 0;
      int64_t smallest = std::numeric_limits<int64_t>::max();
      int64_t largest = std::numeric_limits<int64_t>::min();
      for (int k = i; k < j; ++k) {
        current_sum += valid_numbers[k];
        if (valid_numbers[k] < smallest)
          smallest = valid_numbers[k];
        if (valid_numbers[k] > largest)
          largest = valid_numbers[k];
      }
      if (current_sum == key) {
        printf("smallest value in sum sequence is %lld, largest is %lld\n", smallest, largest);
        printf("their sum is %lld\n", smallest + largest);
        found = true;
        break;
      }
      if (current_sum > key) {
        break;
      }
    }
    if (found)
      break;
  }


  return 0;
}
