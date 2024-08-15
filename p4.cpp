#include <iostream>
#include <string>
#include <vector>
#include "sparrow.h"

using namespace sparrow;

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::vector<std::string> inputs;
        for (int i = 1; i < argc; i++) {
            inputs.push_back(argv[i]);
        }

        // 1. Create an IntColumn object from command line arguments
        IntColumn col(inputs);

        // 2. Drop zero values
        col.DropZero();

        // 3. Print out the resulting column
        std::cout << col;

        // Compute and print the average
        auto result = col.Average();
        if (result.ok == true) {
            std::cout << "Avg: " << result.value << std::endl;
        } else {
            std::cout << "Avg: failed" << std::endl;
        }
    } else {
        // No arguments provided case
        std::cout << "IntColumn:" << std::endl;
        std::cout << "Avg: failed" << std::endl;
    }

    return 0;
}