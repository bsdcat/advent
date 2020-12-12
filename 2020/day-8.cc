#include <cstdio>
#include <fstream>
#include <list>
#include <set>
#include <string>
#include <utility>
#include <vector>

enum op {
  OP_UNSPECIFIED = -1,
  NOOP,
  JMP,
  ACC,
};
  
typedef std::pair<op, int> op_val;

bool run_sim(std::vector<op_val> &ram_ops, int flip_index) {
  std::set<int> indices;
  int acc = 0;
  int index = 0;

  while (true) {
    if (indices.find(index) != indices.end()) {
      if (flip_index == -1)
        printf("accumulator is %d\n", acc);
      return false;
    }

    indices.insert(index);
    if (index < 0) {
      printf("got impossible index %d\n", index);
      return false;
    }

    if (static_cast<size_t>(index) >= ram_ops.size()) {
      printf("got to exit, accumulator is %d\n", acc);
      return true;
    }

    op an_op = ram_ops[index].first;
    int val = ram_ops[index].second;
    if (index == flip_index) {
      if (an_op == op::JMP)
        an_op = op::NOOP;
      else if (an_op == op::NOOP)
        an_op = op::JMP;
    }

    switch(an_op) {
    case op::JMP:
      index += val;
      break;
    case op::ACC:
      acc += val;
    case op::NOOP:
      index++;
      break;
    case op::OP_UNSPECIFIED:
      printf("that broke\n");
      exit(1);
    }
  }
}

int main(int argc, char *argv[]) {
  std::ifstream input = std::ifstream("day-8-input.txt");
  if (!input.is_open())
    return 1;

  std::list<op_val> ops;
  
  char line[256] = {0};
  char word[32] = {0};
  while (input.getline(line, 256)) {
    std::string linestr(line);
    int val = std::stoi(linestr.substr(4));
    std::string opname = linestr.substr(0, 3);
    op an_op = op::OP_UNSPECIFIED;
    if (opname == "jmp") {
      an_op = op::JMP;
    } else if (opname == "nop") {
      an_op = op::NOOP;
    } else if (opname == "acc") {
      an_op = op::ACC;
    }
    ops.push_back(op_val(an_op, val));
  }

  std::vector<op_val> ram_ops = std::vector<op_val>(ops.begin(), ops.end());

  run_sim(ram_ops, -1);
  for (int i = 0; i < ram_ops.size(); ++i) {
    if (run_sim(ram_ops, i))
      break;
  }
  
  return 0;
}
