#include <iostream>
#include <string>
#include <vector>
#include "sparrow.h"

using namespace sparrow;
using namespace std;

int main(int argc, char* argv[]) {
    // cout << "argc: " << argc << endl;
    // for (int i = 0; i < argc; i++) {
    //     cout << "argv[" << i << "]: " << argv[i] << endl;
    // }

    vector<string> inputs;

    // get the information from command line into "inputs"
    for (size_t i = 1; i < argc; i++) {
        inputs.push_back(argv[i]); // adding everything except the first argument ./p3
    }

    NullableInts* nullableInts = StrsToNullableInts(inputs); // this nullableInts is on the heap now since
    // we declared it in the function in sparrow.cpp

    if (nullableInts == nullptr) {
        exit(1);
    }
    // this is using the overload reference one (&) with *nullableInts
    AverageResult averageVal = Average(*nullableInts); // we can have nullableInts which will use the original Average function

    delete nullableInts;// to save heap memory and free up sapce

    if (averageVal.ok == true) {
        cout << averageVal.value << endl; // average val
    } else {
        cout << "failed" << endl; // for stuff like null null
    }
    return 0;
}
