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
  std::set<size_t> indices;
  int acc = 0;
  size_t index = 0;

  while (true) {
    if (indices.find(index) != indices.end()) {
      printf("accumulator is %d\n", acc);
      break;
    }

    indices.insert(index);
    switch(ram_ops[index].first) {
    case op::JMP:
      index += ram_ops[index].second;
      break;
    case op::ACC:
      acc += ram_ops[index].second;
    case op::NOOP:
      index++;
      break;
    case op::OP_UNSPECIFIED:
      printf("that broke\n");
      return 1;
    }
  }
  
  return 0;
}
