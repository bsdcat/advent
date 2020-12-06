#include <cstdio>
#include <fstream>
#include <map>
#include <set>

int main(int argc, char *argv[]) {
  std::ifstream input = std::ifstream("day-6-input.txt");
  if (!input.is_open())
    return 1;

  char line[256] = {0};
  int part_1 = 0;
  int part_2 = 0;
  std::set<char> answers;

  std::map<char, int> answer_count;
  int group_size = 0;
  bool new_group = true;

  while (input.getline(line, 256)) {
    int length = input.gcount();
    if (length > 1) {
      if (new_group) {
        group_size = 0;
        new_group = false;
      }
      group_size++;
      for (int i = 0; i < length - 1; ++i) {
        answers.insert(line[i]);
        answer_count[line[i]]++;
      }
    } else {
      part_1 += answers.size();
      for (auto it = answer_count.begin(); it != answer_count.end(); ++it) {
        if (it->second == group_size) {
          part_2++;
        }
      }
      answers.clear();
      answer_count.clear();
      new_group = true;
    }
  }
  part_1 += answers.size();
  for (auto it = answer_count.begin(); it != answer_count.end(); ++it) {
    if (it->second == group_size) {
      part_2++;
    }
  }

  printf("Sum for part 1 is %d\n", part_1);
  printf("Sum for part 2 is %d\n", part_2);
  
  return 0;
}
