#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
#include <cstring>
#include "sparrow.h"

using namespace std;

std::string IntColumnToStr(sparrow::IntColumn& col) {
  std::ostringstream tout;
  tout << col;
  return tout.str();  
}

void Check(std::string name, sparrow::IntColumn& col, sparrow::IntColumn& expected_col) {
  auto s = IntColumnToStr(col);
  auto expected = IntColumnToStr(expected_col);

  cout << name << ": got\n```" << s << "'''\n";
  if (s == expected) {
    cout << "Good!\n";
  } else {
    cout << "Expected:\n```" << expected << "'''\n";
    std::exit(1);
  }
  cout << "\n";
}

int main(int argc, char* argv[]) {
  {
    auto col = sparrow::NamedIntColumn("col1",
                                       vector<string>{
                                         "9", "8", "null", "7", "null", "6",
                                       });
    assert(col.name == "col1");
    auto expected = sparrow::IntColumn(vector<string>{
        "9", "8", "null", "7", "null", "6",
      });
    Check("A", *col.col, expected);
  }

  {
    auto col = sparrow::NamedIntColumn("col2", vector<string>{});
    assert(col.name == "col2");
    auto expected = sparrow::IntColumn(vector<string>{});
    Check("B", *col.col, expected);
  }

  {
    auto col = new sparrow::NamedIntColumn("col3",
                                           vector<string>{
                                             "9", "8", "null", "7", "null", "6",
                                           });
    constexpr auto size = sizeof(*col->col);
    char bytesBefore[size];
    char bytesAfter[size];

    auto addr = col->col.get();
    std::memcpy(bytesBefore, addr, size);
    delete col;

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
}