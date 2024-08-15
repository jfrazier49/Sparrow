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
std::ostream& operator<<(std::ostream &os, const sparrow::NullableInts &obj) {
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

void Check(std::string name, const sparrow::NullableInts nints, sparrow::AverageResult expected) {
  bool valid = true;

  cout << name << ": calling Average on this (reference):\n" << nints;
  sparrow::AverageResult result = sparrow::Average(nints);
  cout << "Got back: " << result.value << ", ok=" << result.ok << "\n";

  auto diff = result.value - expected.value;
  if (diff < 0)
    diff *= -1;

  if (result.ok != expected.ok) {
    valid = false;
    cout << "We expected ok=" << expected.ok << "\n";
  } else if (result.ok and diff > 0.1) {
    valid = false;
    cout << "We expected " << expected.value << "\n";
  }

  if (valid) {
    cout << "Good!\n\n";
  } else {
    cout << "Exiting with status code 1.\n\n";
    std::exit(1);
  }
}

void Check(std::string name, const sparrow::NullableInts *nints, sparrow::AverageResult expected) {
  bool valid = true;

  if (nints)
    cout << name << ": calling Average on this (pointer):\n" << *nints;
  else
    cout << name << ": calling Average on nullptr\n";
  sparrow::AverageResult result = sparrow::Average(nints);
  cout << "Got back: " << result.value << ", ok=" << result.ok << "\n";

  auto diff = result.value - expected.value;
  if (diff < 0)
    diff *= -1;

  if (result.ok != expected.ok) {
    valid = false;
    cout << "We expected ok=" << expected.ok << "\n";
  } else if (result.ok and diff > 0.1) {
    valid = false;
    cout << "We expected " << expected.value << "\n";
  }

  if (valid) {
    cout << "Good!\n\n";
  } else {
    cout << "Exiting with status code 1.\n\n";
    std::exit(1);
  }
}

int main() {
  {
    sparrow::NullableInts nints{.nums={1,2,3,4,5,7,8,9,10},
                                .valid=vector{bitset<32>{"00000000000000000000000000011111"}}};
    sparrow::AverageResult expected{3.0, true};
    Check("A", nints, expected);
  }

  {
    sparrow::NullableInts nints{.nums={0,0,0,0,0},
                                .valid=vector{bitset<32>{"00000000000000000000000000010000"}}};
    sparrow::AverageResult expected{0.0, true};
    Check("B", nints, expected);
  }

  {
    sparrow::NullableInts nints{.nums={1,2,3,4,5},
                                .valid=vector{bitset<32>{"00000000000000000000000000011100"}}};
    sparrow::AverageResult expected{4.0, true};
    Check("C", nints, expected);
  }

  {
    sparrow::NullableInts nints{.nums={1,2,3,4,5},
                                .valid=vector{bitset<32>{"00000000000000000000000000011000"}}};
    sparrow::AverageResult expected{4.5, true};
    Check("D", nints, expected);
  }

  {
    sparrow::NullableInts nints{.nums={2,1,0,0,3},
                                .valid=vector{bitset<32>{"00000000000000000000000000000000"}}};
    sparrow::AverageResult expected{0.0, false};
    Check("E", nints, expected);
  }

  {
    sparrow::NullableInts nints{.nums={1,2,3,4,5,7,8,9,10},
                                .valid=vector{bitset<32>{"00000000000000000000000000011111"}}};
    sparrow::AverageResult expected{3.0, true};
    Check("F", &nints, expected);
  }

  {
    sparrow::AverageResult expected{0.0, false};
    Check("G", nullptr, expected);
  }
}