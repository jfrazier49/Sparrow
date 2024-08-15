#include <iostream>
#include <vector>
#include "sparrow.h"

using namespace std;

int main(int argc, char* argv[]) {
  {
    cout << "construct with just ints\n";
    vector<string> args{"3", "4", "-1", "0"};
    auto col = sparrow::IntColumn(args);
  }

  {
    cout << "construct with ints and nulls\n";
    vector<string> args{"null", "3", "4", "null", "-1", "0", "null"};
    auto col = sparrow::IntColumn(args);
  }

  {
    cout << "construct with just nulls\n";
    vector<string> args{"null", "null"};
    auto col = sparrow::IntColumn(args);
  }

  {
    cout << "construct nothing\n";
    auto col = sparrow::IntColumn();
  }

  {
    cout << "copy constructor\n";
    auto col1 = sparrow::IntColumn();
    sparrow::IntColumn col2 = col1;
  }

  {
    cout << "copy assignment op\n";
    auto col1 = sparrow::IntColumn();
    sparrow::IntColumn col2;
    col2 = col1;
  }
}