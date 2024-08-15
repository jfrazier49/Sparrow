#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
#include <cstring>
#include "sparrow.h"

using namespace std;
using namespace sparrow;

int main(int argc, char* argv[]) {
  Table t;
  t.AddCol(NamedIntColumn("A", {"1", "2", "null"}));
  const auto col2 = NamedIntColumn("B", {"1", "2", "null"});
  t.AddCol(col2);
  std::vector<std::string> col3vals{"4", "null", "6"};
  auto col3 = std::make_shared<NamedIntColumn>("C", col3vals);
  assert(col3.use_count() == 1);
  t.AddCol(col3);
  assert(col3.use_count() == 2);
  auto t2 = new Table{};
  t2->AddCol(col3);
  assert(col3.use_count() == 3);
  delete t2;
  assert(col3.use_count() == 2);
}