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
  auto col2 = sparrow::NamedIntColumn("tmp",
                                      vector<string>{
                                        "1", "2", "3"
                                      });

  constexpr auto size = sizeof(*col2.col);
  char bytesBefore[size];
  char bytesAfter[size];

  auto addr = col2.col.get();
  std::memcpy(bytesBefore, addr, size);

  col2 = col1; // copy assignment operator!
  
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

  /*
    this is a somewhat risky test!  because we access memory that
    is supposed to be freed (because we want to check that it HAS
    been freed).

    what will typically happen: the memory will still be a valid
    mapping in the address space, but it will get clobbered with
    garbage (malloc/free will typically do this in debug mode to
    help you catch memory issues).  Thus, we expecte the bytes at
    col->col will have changed after a properly written destructor
    runs on col.

    Other things that could happen: malloc doesn't clobber the
    memory, or there is an munmap that is done after the free.  In
    these cases, the assert may fail, or we could segfault.  If
    that happens, we might need to discard this part of the test.
  */
  std::memcpy(bytesAfter, addr, size);
  assert(std::memcmp(bytesBefore, bytesAfter, size) != 0);
}