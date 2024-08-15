#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
#include <cstring>
#include "sparrow.h"

using namespace std;

int main(int argc, char* argv[]) {
  auto col1 = sparrow::NamedIntColumn("col1",
                                      vector<string>{
                                        "9", "8", "null", "7", "null", "6",
                                      });
  auto col2 = col1; // copy constructor!
  cout << "check name...\n";
  assert(col1.name == col2.name);
  assert(col1.name.c_str() != col2.name.c_str());
  cout << "check col...\n";
  assert(col1.col != col2.col);
  assert(col1.col->Size() == col2.col->Size());  
  for (int i=0; i<col1.col->Size(); i++) {
    cout << "check index " << i << "...\n";
    const int *x = (*col1.col)[i];
    const int *y = (*col2.col)[i];
    if (!x) {
      assert(!y);
    } else {
      assert(y);
      assert(*x == *y);
    }
  }
}