#include <cstdio>
#include <fstream>
#include <set>

int main(int argc, char *argv[]) {
  std::ifstream input = std::ifstream("day-6-input.txt");
  if (!input.is_open())
    return 1;

  char line[256] = {0};
  int sum = 0;
  std::set<char> answers;

  while (input.getline(line, 256)) {
    //printf("line is %s\n", line);
    int length = input.gcount();
    //printf("length is %\n", length);
    if (length > 1) {
      printf("%s", line);
      for (int i = 0; i < length - 1; ++i) {
        //printf("%c", line[i]);
        answers.insert(line[i]);
      }
      printf(" %lu\n", answers.size());
      printf("\n");
    } else {
      // printf("got here\n");
      sum += answers.size();
      answers.clear();
    }
  }
  sum += answers.size();

  printf("Sum for part 1 is %d\n", sum);
  
  return 0;
}
