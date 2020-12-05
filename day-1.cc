#include <cstdio>
#include <list>

int main(int argc, char *argv[]) {
  FILE *input = fopen("day-1-input.txt", "r");
  if (!input) return 1;

  std::list<int64_t> expenses;
  int64_t expense;

  while (fscanf(input, "%lld", &expense) > 0)
    expenses.push_back(expense);

  bool part_1 = false;
  bool part_2 = false;

  for (std::list<int64_t>::iterator it = expenses.begin(); it != expenses.end(); ++it) {
    std::list<int64_t>::iterator jt = it;
    ++jt;
    for (; jt != expenses.end(); ++jt) {
      if (!part_1 && *it + *jt == 2020) {
        part_1 = true;
        printf("part 1 answer is %lld\n", *it * *jt);
      }
      std::list<int64_t>::iterator kt = jt;
      ++kt;
      for (; kt != expenses.end(); ++kt) {
        if (!part_2 && *it + *jt + *kt == 2020) {
          printf("result is %lld\n", *it * *jt * *kt);
          part_2 = true;
        }
        if (part_1 && part_2)
          return 0;
      }
    }
  }
  printf("No result found.\n");

  return 0;
}
