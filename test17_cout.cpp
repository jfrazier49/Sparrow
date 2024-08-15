#include <iostream>
#include <vector>
#include <sstream>
#include "sparrow.h"

using namespace std;

void Check(std::string name, sparrow::IntColumn& col, std::string expected) {
  std::ostringstream tout;
  tout << col;
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
    cout << "construct with just ints\n";
    vector<string> args{"3", "4", "-1", "0"};
    auto col = sparrow::IntColumn(args);
    Check("A", col, "IntColumn:\n3\n4\n-1\n0\n");
  }

  {
    cout << "construct with ints and nulls\n";
    vector<string> args{"null", "3", "4", "null", "-1", "0", "null"};
    auto col = sparrow::IntColumn(args);
    Check("B", col, "IntColumn:\nnull\n3\n4\nnull\n-1\n0\nnull\n");
  }
}