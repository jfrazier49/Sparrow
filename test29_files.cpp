#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cassert>
#include "sparrow.h"

using namespace std;
using namespace sparrow;

int main(int argc, char* argv[]) {
  {
    auto f = ofstream{"tbl.txt"};
    f << "2\n"; // rows
    f << "2\n"; // columns
    f << "A\n" << "1\n" << "2\n"; // column A
    f << "B\n" << "3\n" << "4\n"; // column B
  }
  {
    Table t{"tbl.txt"};
    assert(*(*t["A"]->col)[0] == 1);
    assert(*(*t["A"]->col)[1] == 2);
    assert(*(*t["B"]->col)[0] == 3);
    assert(*(*t["B"]->col)[1] == 4);
  }

  {
    auto f = ofstream{"tbl2.txt"};
    f << "2\n"; // rows
    f << "2\n"; // columns
    f << "A\n" << "1\n" << "2\n"; // column A
    f << "B\n" << "3\n" << "5\n"; // column B
  }
  {
    Table t{"tbl2.txt"};
    assert(*(*t["A"]->col)[0] == 1);
    assert(*(*t["A"]->col)[1] == 2);
    assert(*(*t["B"]->col)[0] == 3);
    assert(*(*t["B"]->col)[1] == 5);
  }

  {
    auto f = ofstream{"tbl.txt"};
    f << "3\n"; // rows
    f << "1\n"; // columns
    f << "A\n" << "1\n" << "null\n" << "2\n"; // column A
  }
  {
    Table t{"tbl.txt"};
    assert(*(*t["A"]->col)[0] == 1);
    assert((*t["A"]->col)[1] == nullptr);
    assert(*(*t["A"]->col)[2] == 2);
  }  
}