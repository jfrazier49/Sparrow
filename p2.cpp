#include <iostream>
#include <vector>
#include <bitset>
#include "sparrow.h"
using namespace sparrow; // no need to have sparrow:: in front of stuff now
using namespace std; // no need to have std:: in front of stuff now

int main() {
    NullableInts nints1{.nums={20,999,40,60}, .valid=vector<bitset<32>>{bitset<32>("00000000000000000000000000001101")}};
    NullableInts nints2{.nums={10,10,0,20}, .valid=vector<bitset<32>>{bitset<32>("00000000000000000000000000001111")}};

    // Drop zeros from the denominator as instructed to prevent divide by 0 errors
    DropZero(&nints2);

    DivideResult divResult = Divide(&nints1, &nints2);
    if (divResult.ok == false) {
        exit(1);
    }

    AverageResult averageOfDiv = Average(&divResult.value);
    if (averageOfDiv.ok == false) {
        exit(1); // Indicates failure
    }

    cout << averageOfDiv.value << endl;
    return 0;
}
