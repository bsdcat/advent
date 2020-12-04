#include <cstdio>
#include <list>

int main(int argc, char *argv[]) {
  FILE *input = fopen("day-1-input.txt", "r");
  if (!input) return 1;

  std::list<int64_t> expenses;
  int64_t expense;

  while (fscanf(input, "%lld", &expense) > 0)
    expenses.push_back(expense);

  for (std::list<int64_t>::iterator it = expenses.begin(); it != expenses.end(); ++it) {
    std::list<int64_t>::iterator jt = it;
    ++jt;
    for (; jt != expenses.end(); ++jt) {
      std::list<int64_t>::iterator kt = jt;
      ++kt;
      for (; kt != expenses.end(); ++kt) {
        if (*it + *jt + *kt == 2020) {
          printf("result is %lld\n", *it * *jt * *kt);
          return 0;
        }
      }
    }
  }
  printf("No result found.\n");

  return 0;
}
