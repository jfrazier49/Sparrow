#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
#include <cstring>
#include "sparrow.h"

using namespace std;
using namespace sparrow;

int main(int argc, char* argv[]) {
  std::vector<std::string> col1vals{"4", "null", "6"};
  auto col1 = std::make_shared<NamedIntColumn>("A", col1vals);
  std::vector<std::string> col2vals{"1", "2", "3"};
  auto col2 = std::make_shared<NamedIntColumn>("B", col2vals);
  std::vector<std::string> col3vals{"7", "8", "9"};
  auto col3 = std::make_shared<NamedIntColumn>("C", col3vals);

  Table t;
  t.AddCol(col1);
  assert(t["A"].get() == col1.get());
  t.AddCol(col2);
  assert(t["A"].get() == col1.get());
  assert(t["B"].get() == col2.get());
  t.AddCol(col3);
  assert(t["A"].get() == col1.get());
  assert(t["B"].get() == col2.get());
  assert(t["C"].get() == col3.get());

  assert(col3.use_count() == 2);
  Table t2;
  t2.AddCol(t["C"]);
  assert(col3.use_count() == 3);
  auto col3b = t2["C"];
  assert(col3.use_count() == 4);
  assert(col3.get() == col3b.get());
}