#include <algorithm>
#include <cstdio>
#include <fstream>
#include <list>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::ifstream input = std::ifstream("day-10-input.txt");
  if (!input.is_open())
    return 1;

  std::vector<int64_t> adapters;
  char line[256];
  while (input.getline(line, 256)) {
    std::string linestr(line);
    int64_t val = std::stoll(linestr);
    adapters.push_back(val);
  }

  std::sort(adapters.begin(), adapters.end());
  adapters.push_back(*(adapters.rbegin()) + 3);

  int one_jolt = 0;
  int three_jolt = 0;
  int64_t cur_jolt = 0;
  for (int64_t jolts : adapters) {
    if (jolts - cur_jolt == 1)
      ++one_jolt;
    if (jolts - cur_jolt == 3)
      ++three_jolt;
    cur_jolt = jolts;
  }

  printf("There are %d one-jolt differences and %d three-jolt differences, producing %d\n",
         one_jolt, three_jolt, one_jolt * three_jolt);

  return 0;
}
