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

void Check(std::string name, sparrow::NullableInts nints, sparrow::NullableInts expected) {
  bool valid = true;

  cout << name << ": calling DropZero on this:\n" << nints;
  sparrow::DropZero(&nints);
  cout << "Got back: " << nints;

  // check that numbers match
  if (nints.nums.size() != expected.nums.size()) {
    // size mismatch
    valid = false;
  } else {
    // check all valid bits match
    for (int i=0; i<nints.nums.size(); i++) {
      if (i/32 > nints.valid.size() or i%32 > nints.valid[i/32].size()) {
        // not enough valid bits given how many numbers there are
        valid = false;
      } else if (nints.valid[i/32][i%32] != expected.valid[i/32][i%32]) {
        // valid bits not as expected
        valid = false;
      } else if (nints.valid[i/32][i%32] and nints.nums[i] != expected.nums[i]) {
        // numbers marked valid differ
        valid = false;
      }
    }
  }

  if (valid) {
    cout << "Good!\n\n";
  } else {
    cout << "Expected " << expected << "Exiting with status code 1.\n\n";
    std::exit(1);
  }
}

int main() {
  {
    sparrow::NullableInts nints{.nums={1,2,3,4,5},
                                .valid=vector{bitset<32>{"00000000000000000000000000011111"}}};
    sparrow::NullableInts expected{.nums={1,2,3,4,5},
                                   .valid=vector{bitset<32>{"00000000000000000000000000011111"}}};
    Check("A", nints, expected);
  }

  {
    sparrow::NullableInts nints{.nums={1,2,3,4,5},
                                .valid=vector{bitset<32>{"00000000000000000000000000011011"}}};
    sparrow::NullableInts expected{.nums={1,2,3,4,5},
                                   .valid=vector{bitset<32>{"00000000000000000000000000011011"}}};
    Check("B", nints, expected);
  }

  {
    sparrow::NullableInts nints{.nums={0,-1,3,4,0},
                                .valid=vector{bitset<32>{"00000000000000000000000000011011"}}};
    sparrow::NullableInts expected{.nums={-1,-1,3,4,-1},
                                   .valid=vector{bitset<32>{"00000000000000000000000000001010"}}};
    Check("C", nints, expected);
  }

  {
    sparrow::NullableInts nints{.nums={0,7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
                                       9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,0,
                                       9,0,0,9,9,9,9,9,9,9,9,9,9,9,9,9,
                                       9,9,9,9,9,9,9,9,9,9,9,9,0,0,0,-9,},
                                .valid=vector{bitset<32>{"11111111111111111111111111111111"},
                                              bitset<32>{"11111111111111111111111111111111"}}};
    sparrow::NullableInts expected{.nums={9,7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
                                          9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
                                          9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
                                          9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,-9,},
                                   .valid=vector{bitset<32>{"01111111111111111111111111111110"},
                                                 bitset<32>{"10001111111111111111111111111001"}}};
    Check("D", nints, expected);
  }
}