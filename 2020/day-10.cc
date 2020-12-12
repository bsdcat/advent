#include <algorithm>
#include <cstdio>
#include <fstream>
#include <set>
#include <string>
#include <vector>

int64_t count_perms(std::vector<int64_t> &adapters, std::vector<int64_t> &seen, int cur_index) {
  if (cur_index == adapters.size() - 1)
    return 1;

  if (cur_index >= 0 && seen[cur_index] >= 0)
    return seen[cur_index];

  int64_t sum = 0;
  int cur_jolts = 0;
  if (cur_index >= 0)
    cur_jolts = adapters[cur_index];
  for (int i = cur_index + 1; i < cur_index + 4 && i < adapters.size(); ++i) {
    if (adapters[i] > cur_jolts + 3)
      break;
    sum += count_perms(adapters, seen, i);
  }
  seen[cur_index] = sum;
  return sum;
}

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

  std::vector<int64_t> seen(adapters.size(), -1LL);
  printf("There are %lld permutations of adapters\n", count_perms(adapters, seen, -1));

  return 0;
}
