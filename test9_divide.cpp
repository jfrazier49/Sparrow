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
  if (obj.nums.size() > obj.valid.size() * 32) {
    cout << "INVALID NullableInts!\n";
    return os;
  }

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

void Check(sparrow::NullableInts nints, sparrow::NullableInts expected) {
  bool valid = true;

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

void Check(std::string name,
           sparrow::NullableInts nints1,
           sparrow::NullableInts nints2,
           sparrow::DivideResult expected) {
  bool valid = true;

  cout << name << ": calling Divide on these:\n" << nints1 << nints2;
  sparrow::DivideResult result = sparrow::Divide(&nints1, &nints2);
  cout << "Got back: ok=" << result.ok << ", value=" << result.value << "\n";

  if (result.ok != expected.ok) {
    valid = false;
    cout << "We expected ok=" << expected.ok << "\n";
    cout << "Exiting with status code 1.\n\n";
    std::exit(1);
  }
  Check(result.value, expected.value);
}

int main() {
  {
    sparrow::NullableInts nints1{
      .nums={7,8,9},
      .valid=vector{bitset<32>{"00000000000000000000000000000011"}}
    };
    sparrow::NullableInts nints2{
      .nums={3,2,1},
      .valid=vector{bitset<32>{"00000000000000000000000000000110"}}
    };
    sparrow::DivideResult expected{
      {
        .nums={-1,4,-1},
        .valid=vector{bitset<32>{"00000000000000000000000000000010"}}
      },
      true
    };
    Check("A", nints1, nints2, expected);
  }

  {
    sparrow::NullableInts nints1{
      .nums={7,8,9},
      .valid=vector{bitset<32>{"00000000000000000000000000000011"}}
    };
    sparrow::NullableInts nints2{
      .nums={0,2,0},
      .valid=vector{bitset<32>{"00000000000000000000000000000110"}}
    };
    sparrow::DivideResult expected{
      {
        .nums={-1,4,-1},
        .valid=vector{bitset<32>{"00000000000000000000000000000010"}}
      },
      true
    };
    Check("B", nints1, nints2, expected);
  }

  {
    sparrow::NullableInts nints1{
      .nums={12,8,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
             12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
             12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
             12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,},
      .valid=vector{bitset<32>{"11111111111111111111111111111111"},
                    bitset<32>{"01111111111111111111111111111111"}}
    };
    sparrow::NullableInts nints2{
      .nums={2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
             4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
             4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
             4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,},
      .valid=vector{bitset<32>{"11111111111111111111111111111111"},
                    bitset<32>{"10111111111111111111111111111111"}}
    };
    sparrow::DivideResult expected{
      {
      .nums={6,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
             3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
             3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
             3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
      .valid=vector{bitset<32>{"11111111111111111111111111111111"},
                    bitset<32>{"00111111111111111111111111111111"}}
      },
      true
    };
    Check("C", nints1, nints2, expected);
  }

  {
    sparrow::NullableInts nints1{
      .nums={12,8,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
             12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
             12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
             12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,},
      .valid=vector{bitset<32>{"11111111111111111111111111111111"},
                    bitset<32>{"01111111111111111111111111111111"}}
    };
    sparrow::NullableInts nints2{
      .nums={2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
             4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
      },
      .valid=vector{bitset<32>{"11111111111111111111111111111111"}}
    };
    sparrow::DivideResult expected{
      {
      .nums={},
      .valid={}
      },
      false
    };
    Check("D", nints1, nints2, expected);
  }
}