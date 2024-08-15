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

void Check(std::string name, vector<bitset<32>> bits, unsigned expected) {
  unsigned count = sparrow::warmup::CountBits(bits);
  cout << name << ": sparrow::warmup::CountBits(" << bits << ") returned " << count << ".\n";
  if (count == expected) {
    cout << "Good!\n\n";
  } else {
    cout << "Expected " << expected << ".  Exiting with status code 1.\n\n";
    std::exit(1);
  }
}

int main() {
  Check("A",
        vector{bitset<32>{"00000000000000000000000000000000"},
               bitset<32>{"00000000000000000000000000000000"},},
        0);
  Check("B",
        vector<bitset<32>>{},
        0);
  Check("C",
        vector{bitset<32>{"10000000000000000000000000000000"},
               bitset<32>{"00000000000000000000000000000011"},
               bitset<32>{"00000000000000100000000000000000"},
               bitset<32>{"10000000000000000000000000100000"},
               bitset<32>{"00001000001000000000001000001000"},},
        10);
  Check("D",
        vector{bitset<32>{"11111111111111111111111111111111"},
               bitset<32>{"11111111111111111111111111111111"},
               bitset<32>{"11111111111111111111111111111111"},
               bitset<32>{"11111111111111111111111111111111"},
               bitset<32>{"11111111111111111111111111111111"},},
        5*32);
  Check("E",
        vector{bitset<32>{"01010101010101010101010101010101"}},
        16);
  Check("F",
        vector{bitset<32>{"11010101010101010101010101010101"}},
        17);
}