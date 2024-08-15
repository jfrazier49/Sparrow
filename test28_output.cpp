#include <iostream>
#include <vector>
#include <sstream>
#include "sparrow.h"

using namespace std;
using namespace sparrow;

void Check(std::string name, sparrow::Table& tbl, std::string expected) {
  std::ostringstream tout;
  tout << tbl;
  auto s = tout.str();
  cout << name << ": got\n```" << s << "'''\n";
  if (s == expected) {
    cout << "Good!\n";
  } else {
    cout << "Expected:\n```" << expected << "'''\n";
    std::exit(1);
  }
  cout << "\n";
}

int main(int argc, char* argv[]) {
  {
    Table t;
    t.AddCol(NamedIntColumn("A", {"1", "2", "null"}));
    std::vector<std::string> col2vals{"4", "null", "6"};
    auto col2 = std::make_shared<NamedIntColumn>("B", col2vals);
    t.AddCol(col2);
    Check("A", t, "A,B\n1,4\n2,null\nnull,6\n");
  }

  {
    Table t;
    t.AddCol(NamedIntColumn("test", {"1", "2", "null", "4", "-5"}));
    Check("B", t, "test\n1\n2\nnull\n4\n-5\n");
  }  
}