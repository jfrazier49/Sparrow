#include <cstdlib>
#include <iostream>
#include <bitset>
#include "sparrow.h"

using std::cout;
using std::bitset;

void Check(std::string name, bitset<32> bits, unsigned pos, unsigned len, unsigned expected) {
  unsigned count = sparrow::warmup::CountBits(bits, pos, len);
  cout << name << ": sparrow::warmup::CountBits(bitset<32>{" << bits << "}, " << pos << ", " << len << ") returned " << count << ".\n";
  if (count == expected) {
    cout << "Good!\n\n";
  } else {
    cout << "Expected " << expected << ".  Exiting with status code 1.\n\n";
    std::exit(1);
  }
}

int main() {
  Check("A", bitset<32>{"00000000000000000000000000000000"}, 0, 32, 0);
  Check("B", bitset<32>{"11111111111111111111111111111111"}, 0, 32, 32);
  Check("C", bitset<32>{"10000000000000000000000000000001"}, 0, 32, 2);
  Check("D", bitset<32>{"10000000000000000000000000000001"}, 0, 31, 1);
  Check("E", bitset<32>{"10000000000000000000000000000001"}, 1, 31, 1);
  Check("F", bitset<32>{"10000000000000000000000000000001"}, 1, 1000, 1);
  Check("G", bitset<32>{"10000000000000000000000000000001"}, 100, 1000, 0);
  Check("H", bitset<32>{"00000000000000000000000000000111"}, 0, 4, 3);
  Check("I", bitset<32>{"10101010101010101010101010101010"}, 1, 31, 16);
}