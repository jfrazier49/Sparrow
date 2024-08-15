#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cassert>
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
    auto f = ofstream{"tbl.txt"};
    f << "3\n"; // rows
    f << "2\n"; // columns
    f << "A\n" << "10\n" << "20\n" << "30\n"; // column A
    f << "B\n" << "10\n" << "5\n" << "15\n";  // column B
  }
  {
    Table t{"tbl.txt"};
    Check("B", t, "A,B\n10,10\n20,5\n30,15\n");
    t.AddCol(*t["A"] / *t["B"]);
    Check("B", t, "A,B,A/B\n10,10,1\n20,5,4\n30,15,2\n");
    t.AddCol(*t["A"] / 10);
    Check("C", t, "A,B,A/B,A/10\n10,10,1,1\n20,5,4,2\n30,15,2,3\n");
  }
}