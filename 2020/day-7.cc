#include <cstdio>
#include <fstream>
#include <list>
#include <map>
#include <set>
#include <string>

struct bag {
  std::string name;
  std::map<std::string, int> contains;
};

uint64_t count_bags(const std::string &name, std::map<std::string, bag *> &bag_map) {
  static std::map<std::string, uint64_t> seen_bags;
  auto it = seen_bags.find(name);
  if (it != seen_bags.end()) {
    return it->second;
  }

  printf("checking for bags I need in a '%s' bag\n", name.c_str());
  bag *this_bag = bag_map[name];
  uint64_t accumulator = 0;
  for (const std::pair<std::string, int> &container : this_bag->contains) {
    accumulator += container.second;
    accumulator += container.second * count_bags(container.first, bag_map);
  }
  seen_bags[name] = accumulator;
  return accumulator;
}

int main(int argc, char *argv[]) {
  std::ifstream input = std::ifstream("day-7-input.txt");
  if (!input.is_open())
    return 1;
  
  std::map<std::string, bag *> bag_map;
  char line[256] = {0};
  char word[32] = {0};
  while (input.getline(line, 256)) {
    std::string linestr(line);
    size_t offset = linestr.find(" bags contain ");
    std::string name = linestr.substr(0, offset);
    bag * new_bag = new bag();
    new_bag->name = name;
    bag_map[name] = new_bag;
    //  printf("bag type is %s\n", name.c_str());
    offset += 14;
    while (offset != std::string::npos) {
      int count = 0;
      if (linestr.substr(offset) != "no other bags.") {
        count = std::stoi(linestr.substr(offset));
        size_t after_num_offset = linestr.find(" ", offset);
        size_t bag_offset = linestr.find(" bag", after_num_offset);
        std::string contains = linestr.substr(after_num_offset + 1, bag_offset - after_num_offset - 1);
        new_bag->contains[contains] = count;
        //  printf("\t%d '%s'\n", count, contains.c_str());
        offset = linestr.find_first_of("123456789", after_num_offset);
      } else {
        offset = std::string::npos;
      }
    }
  }

  std::set<std::string> holds_mine;
  std::set<std::string> looking_for;
  looking_for.insert("shiny gold");
  while (!looking_for.empty()) {
    std::string term = *(looking_for.begin());
    for (const std::pair<std::string, bag *> &entry : bag_map) {
      for (const std::pair<std::string, int> &container : entry.second->contains) {
        if (container.first == term) {
          holds_mine.insert(entry.first);
          looking_for.insert(entry.first);
        }
      }
    }
    looking_for.erase(term);
  }

  printf("%lu different bags hold mine.\n", holds_mine.size());

  printf("%llu total bags required.\n", count_bags("shiny gold", bag_map));

  return 0;
}
