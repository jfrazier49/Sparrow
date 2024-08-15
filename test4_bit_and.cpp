#include <cstdlib>
#include <iostream>
#include <bitset>
#include <vector>

#include "sparrow.h"

using std::cout;
using std::bitset;
using std::vector;
using std::ostream;

// so we can easily print vectors of bitsets
ostream& operator<<(ostream &os, vector<bitset<32>> &obj) {
  cout << "\n\tvector{";
  for (auto &chunk : obj) {
    cout << "\n\t\tbitset<32>{" << chunk << "},";
  }
  cout << "\n\t}";
  return os;
}

void Check(std::string name, vector<bitset<32>> a, vector<bitset<32>> b,
           vector<bitset<32>> expected_result, bool expected_ok=true) {
  if (expected_ok != (a.size() == b.size())) {
    throw std::runtime_error("bad test");
  }

  auto [result, ok] = sparrow::warmup::BitAnd(a, b);

  cout << name << ": sparrow::warmup::BitAnd("<< a << ", " << b << ")\n";
  if (ok) {
    cout << "returned:";
    cout << result << "\n";
  } else {
    cout << "returned a failure status (!ok)\n";
  }

  if (ok == expected_ok and result == expected_result) {
    cout << "Good!\n\n";
  } else if (ok and !expected_ok) {
    cout << "Bad!  It was expected to fail given the inputs.\n\n";
    std::exit(1);
  } else if (!ok and expected_ok) {
    cout << "Bad!  It was expected to succeed and return:" << expected_result << "\n\n";
    std::exit(1);
  } else {
    cout << "Bad!  It was expected to return:" << expected_result << "\n\n";
    std::exit(1);
  }
}

int main() {
  Check("A",
        vector{bitset<32>{"11000000000000000000000000000010"}}, // a
        vector{bitset<32>{"01100000000000000000000000000011"}}, // b
        vector{bitset<32>{"01000000000000000000000000000010"}}  // result
        );
  Check("B",
        vector{bitset<32>{"00000000011100000000000000000000"},    // a
               bitset<32>{"00000000000000000000000000000111"},},
        vector{bitset<32>{"00000000001000000000000000000000"},    // b
               bitset<32>{"00000000000000000000000000000100"},},
        vector{bitset<32>{"00000000001000000000000000000000"},
               bitset<32>{"00000000000000000000000000000100"},}  // expected result
        );
  Check("C",
        vector<bitset<32>>{}, // a
        vector<bitset<32>>{}, // b
        vector<bitset<32>>{}  // result
        );
  Check("D",
        vector{bitset<32>{"11000000000000000000000000000010"}}, // a
        vector<bitset<32>>{}, // b
        vector<bitset<32>>{}, // result
        false // should fail
        );
  Check("E",
        vector<bitset<32>>{}, // a
        vector{bitset<32>{"11000000000000000000000000000010"}}, // b
        vector<bitset<32>>{}, // result
        false // should fail
        );
  Check("F",
        vector{bitset<32>{"00000000011100000000000000000000"},    // a
               bitset<32>{"00000000000000000000000000000111"},
               bitset<32>{"00000000011100000000000000000000"},
               bitset<32>{"00000000000000000000000000000111"},
               bitset<32>{"00000000011100000000000000000000"},
               bitset<32>{"00000000000000000000000000000111"},
               bitset<32>{"00000000011100000000000000000000"},
               bitset<32>{"00000000000000000000000000000111"},},
        vector{bitset<32>{"00000000011100000000000000000000"},    // b
               bitset<32>{"00000000000000000000000000000111"},
               bitset<32>{"00000000011100000000000000000000"},
               bitset<32>{"00000000000000000000000000000111"},
               bitset<32>{"00000000011100000000000000000000"},
               bitset<32>{"00000000000000000000000000000111"},
               bitset<32>{"00000000000000000000000000000111"},},
        vector<bitset<32>>{},
        false // should fail
        );
}