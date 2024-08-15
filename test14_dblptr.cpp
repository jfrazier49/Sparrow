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

std::ostream& operator<<(std::ostream &os, std::vector<int> &nums) {
  os << "[";
  for (int i=0; i<nums.size(); i++) {
    os << nums[i];
    if (i < nums.size()-1)
      os << ", ";
  }
  os << "]";
  return os;
}

void Check(std::string name, std::vector<std::string> args, std::vector<int> expected) {
  sparrow::NullableInts* nints = sparrow::StrsToNullableInts(args);
  int *arr;
  auto size = sparrow::NullableIntsToArray(*nints, &arr);

  cout << name << ": calling NullableIntsToArray on this:\n" << *nints;
  cout << "Got back: [";
  for (int i=0; i<size; i++) {
    cout << arr[i];
    if (i < size-1)
      cout << ", ";
  }
  cout << "]\n";

  bool valid = true;
  
  // check that numbers match
  if (size != expected.size()) {
    // size mismatch
    valid = false;
  } else {
    for (int i=0; i<expected.size(); i++) {
      if (expected[i] != arr[i]) {
        valid = false;
        break;
      }
    }
  }

  if (valid) {
    cout << "Good!\n\n";
  } else {
    cout << "Expected: " << expected << "\nExiting with status code 1.\n\n";
    std::exit(1);
  }

  delete nints;
  delete arr;
}

int main() {
  {
    std::vector<std::string> args{"1", "2", "3"};
    std::vector<int> expected{1,2,3};
    Check("A", args, expected);
  }

  {
    std::vector<std::string> args{"null", "1", "null", "2", "null", "3", "null"};
    std::vector<int> expected{1,2,3};
    Check("B", args, expected);
  }

  {
    std::vector<std::string> args{"null", "null"};
    std::vector<int> expected{};
    Check("C", args, expected);
  }

  {
    std::vector<std::string> args{
      "null", "null", "null", "null",
      "null", "3", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "6", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "null", "null", "null", "null",
      "8", "null", "null", "null"
    };
    std::vector<int> expected{3,6,8};
    Check("D", args, expected);
  }
}