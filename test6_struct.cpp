#include <cstdlib>
#include <iostream>
#include <bitset>
#include <vector>
#include "sparrow.h"

using std::cout;
using std::bitset;
using std::vector;
using std::ostream;

// print NullableInts                                                                    
std::ostream& operator<<(std::ostream &os, sparrow::NullableInts &obj) {
  std::cout << "NullableInts: [";
  for (int i=0; i<obj.nums.size(); i++) {
    if (obj.valid[i/32][i%32]) {
      std::cout << obj.nums[i];
    } else {
      std::cout << "null";
    }
    if (i < obj.nums.size()-1) {
      std::cout << ", ";
    }
  }
  std::cout << "]\n";
  return os;
}

int main() {
  sparrow::NullableInts nints1{.nums={20,999,40,60},
                               .valid=vector{bitset<32>{"00000000000000000000000000001101"}}};
  sparrow::NullableInts nints2{.nums={10,10,0,20},
                               .valid=vector{bitset<32>{"00000000000000000000000000001111"}}};
  cout << "Example 1:\n" << nints1 << "\n";
  cout << "Example 2:\n" << nints2 << "\n";
}