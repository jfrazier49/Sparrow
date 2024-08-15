#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
#include "sparrow.h"

using namespace std;

std::string IntColumnToStr(sparrow::IntColumn& col) {
  std::ostringstream tout;
  tout << col;
  return tout.str();  
}

void Check(std::string name, sparrow::IntColumn& col, sparrow::IntColumn& expected_col) {
  auto s = IntColumnToStr(col);
  auto expected = IntColumnToStr(expected_col);

  cout << name << ": got\n```" << s << "'''\n";
  if (s == expected) {
    cout << "Good!\n";
  } else {
    cout << "Expected:\n```" << expected << "'''\n";
    std::exit(1);
  }
  cout << "\n";
}

// just a wrapper around col[idx], but it's nice to call it from a
// different function to catch implementations that are returning the
// addr of a variable on the stack
const int* GetAtIdx(sparrow::IntColumn& col, int idx) {
  return col[idx];
}

int main(int argc, char* argv[]) {
  auto col = sparrow::IntColumn(vector<string>{
      "9", "8", "null", "7", "null", "6",
    });

  cout << "Test positive indexes\n";
  assert(*col[0] == 9);
  assert(*col[1] == 8);
  assert(col[2] == nullptr);
  assert(*col[3] == 7);
  assert(col[4] == nullptr);
  assert(*col[5] == 6);
  cout << "Good!\n";

  cout << "Test negative indexes\n";
  assert(*col[-6] == 9);
  assert(*col[-5] == 8);
  assert(col[-4] == nullptr);
  assert(*col[-3] == 7);
  assert(col[-2] == nullptr);
  assert(*col[-1] == 6);
  cout << "Good!\n";

  cout << "Test memory\n";  
  assert(col[0] == GetAtIdx(col, 0));
  assert(col[-1] == GetAtIdx(col, -1));
  cout << "Good!\n";
}