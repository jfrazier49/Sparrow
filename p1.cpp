#include <iostream>
#include <vector>
#include <bitset>
#include "sparrow.h"

int main() {
    std::bitset<32> bits1("11100000000001100000000000100010");
    std::bitset<32> bits2("01110000000001111000000000100001");

    // auto is same as std::vector<std::bitset<32>> 
    auto [res, isSameLength] = sparrow::warmup::BitAnd({bits1}, {bits2}); // bits1 for a, bits2 for b
    int count = sparrow::warmup::CountBits(res);
    std::cout << count << std::endl;
    return 0;
}
