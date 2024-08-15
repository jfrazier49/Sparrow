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

std::ostream& operator<<(std::ostream &os, std::vector<std::string> &args) {
  os << "[";
  for (int i=0; i<args.size(); i++) {
    os << "\"" << args[i] << "\"";
    if (i < args.size()-1)
      os << ", ";
  }
  os << "]";
  return os;
}

void Check(std::string name, std::vector<std::string> args, sparrow::NullableInts expected) {
  cout << name << ": calling StrsToNullableInts on these: " << args << "\n";
  sparrow::NullableInts* nints = sparrow::StrsToNullableInts(args);
  cout << "Got back: " << *nints << "\n";

  bool valid = true;
  
  // check that numbers match
  if (nints->nums.size() != expected.nums.size()) {
    // size mismatch
    valid = false;
  } else {
    // check all valid bits match
    for (int i=0; i<nints->nums.size(); i++) {
      if (i/32 > nints->valid.size() or i%32 > nints->valid[i/32].size()) {
        // not enough valid bits given how many numbers there are
        valid = false;
      } else if (nints->valid[i/32][i%32] != expected.valid[i/32][i%32]) {
        // valid bits not as expected
        valid = false;
      } else if (nints->valid[i/32][i%32] and nints->nums[i] != expected.nums[i]) {
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

  delete nints;
}

int main() {
  {
    std::vector<std::string> args{"3", "2", "1"};
    sparrow::NullableInts expected{
      .nums={3,2,1},
      .valid=vector{bitset<32>{"00000000000000000000000000000111"}}
    };
    Check("A", args, expected);
  }

  {
    std::vector<std::string> args{"3", "2", "1", "null"};
    sparrow::NullableInts expected{
      .nums={3,2,1,-1},
      .valid=vector{bitset<32>{"00000000000000000000000000000111"}}
    };
    Check("B", args, expected);
  }

  {
    std::vector<std::string> args{"null", "3", "null", "2", "1", "null"};
    sparrow::NullableInts expected{
      .nums={-1,3,-1,2,1,-1},
      .valid=vector{bitset<32>{"00000000000000000000000000011010"}}
    };
    Check("C", args, expected);
  }

  {
    std::vector<std::string> args{"null","7","9","9","9","9","9","9","9","9","9","9","9","9","9","9",
                                  "9","9","9","9","9","9","9","9","9","9","9","9","9","9","9","null",
                                  "9","null","null","9","9","9","9","9","9","9","9","9","9","9","9","9",
                                  "9","9","9","9","9","9","9","9","9","9","9","9","null","null","null","-9",};
    sparrow::NullableInts expected{.nums={9,7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
                                          9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
                                          9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
                                          9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,-9,},
                                   .valid=vector{bitset<32>{"01111111111111111111111111111110"},
                                                 bitset<32>{"10001111111111111111111111111001"}}};
    Check("D", args, expected);
  }
}