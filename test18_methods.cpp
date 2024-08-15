#include <iostream>
#include <vector>
#include <sstream>
#include "sparrow.h"

using namespace std;

void CheckAverage(std::string name, sparrow::IntColumn col, sparrow::AverageResult expected) {
  bool valid = true;

  cout << name << ": calling Average on this:\n" << col;
  sparrow::AverageResult result = col.Average();
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
    cout << "Test DropZero\n";
    auto col = sparrow::IntColumn(vector<string>{
        "0", "3", "4", "0", "-1", "0",
      });
    col.DropZero();
    auto expected = sparrow::IntColumn(vector<string>{
        "null", "3", "4", "null", "-1", "null",
      });
    Check("A", col, expected);
  }

  {
    sparrow::IntColumn col(vector<std::string>{"null", "null", "null", "0"});
    sparrow::AverageResult expected{0.0, true};
    CheckAverage("B", col, expected);
  }

  {
    sparrow::IntColumn col(vector<std::string>{"null", "null", "null", "null"});
    sparrow::AverageResult expected{0.0, false};
    CheckAverage("C", col, expected);
  }

  {
    sparrow::IntColumn col(vector<std::string>{"null", "6", "null", "4"});
    sparrow::AverageResult expected{5.0, true};
    CheckAverage("D", col, expected);
  }

  {
    cout << "Test operator/\n";
    auto col1 = sparrow::IntColumn(vector<string>{
        "10", "8", "null", "0", "4", "9",
      });
    auto col2 = sparrow::IntColumn(vector<string>{
        "2", "2", "0", "2", "null", "3",
      });
    auto result = col1/col2;
    auto expected = sparrow::IntColumn(vector<string>{
        "5", "4", "null", "0", "null", "3",
      });
    Check("E", result, expected);
  }

  {
    cout << "Test all\n";
    auto col1 = sparrow::IntColumn(vector<string>{
        "16", "8", "null", "1", "1", "1",
      });
    auto col2 = sparrow::IntColumn(vector<string>{
        "2", "2", "0", "2", "3", "null",
      });
    auto result = col1/col2;
    result.DropZero();
    sparrow::AverageResult expected{6.0, true};
    CheckAverage("F", result, expected);
  }  
}