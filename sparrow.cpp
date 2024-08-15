#include <iostream>
#include <bitset>
#include <vector>
#include "sparrow.h"
#include <utility>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <stdexcept>


namespace sparrow {

    namespace warmup {
        unsigned CountBits(std::bitset<32> bits, unsigned pos, unsigned len) {

            // if a position is over 32, it's default 0 since you can't have position > 32
            // when the a valid bit length is only until 32
            if (pos > 32) return 0;
            len = std::min(32 - pos, len); // Adjust len accordingly
            int count = 0;

            // Count the set bits within the specified range.
            // i is unsigned, since pos and len are unsigned
            for (unsigned i = pos; i < len + pos; i++) {

                // if we detect a 1 in the bitset
                if (bits.test(i) == true) {
                    count++;
                }
            }

            return count;
        }

        // having const and & for this argument function, this gives better performance
        unsigned CountBits(const std::vector<std::bitset<32>>& bitsets) {
            int total_count = 0;

            for (const std::bitset<32>& bits : bitsets) {
                total_count += bits.count(); // counts all the ones for each bits
            }
            return total_count; // all the total bits from each bits
        }

        std::pair<std::vector<std::bitset<32>>, bool> BitAnd(std::vector<std::bitset<32>> a,
                                                        std::vector<std::bitset<32>> b) {
            
            std::vector<std::bitset<32>> result; // hint from p1 Readme
            
            bool ifSameLength = a.size() == b.size(); // will be the second result in pair

            if (ifSameLength == true) {
                for (size_t i = 0; i < a.size(); i++) {
                    result.push_back(a[i] & b[i]); // hint from p1 Readme
                }
            }

            return {result, ifSameLength};
        }
    }

    void DropZero(NullableInts* nullableInt) {

        if (nullableInt == nullptr) return; 

        int sizeOfBits = nullableInt->nums.size();

        for (int i = 0; i < sizeOfBits; i++) {
            if (nullableInt->nums[i] == 0) { 

                int bitPosition = i % 32;
                // since we could have multiple arrays of individual bitsets
                // we want to know which array the bit is in
                int whichBitset = i / 32;

                nullableInt->valid[whichBitset].set(bitPosition, 0);
                
            }
        }
    }

    AverageResult Average(const NullableInts* nullableInt) {

        // p3 specified to do this, however I already implmemented this check !ok
        // when doing p2
        if (nullableInt == nullptr)    return {0.0, false};
        int numNums = nullableInt->nums.size();

        float sumOfValidNums = 0.0;
        int validBitsCount = 0;

        for (int i = 0; i < numNums; i++) {
            int bitPosition = i % 32;
            int whichBitset = i / 32;

            // update the sum and number of valid bits
            if ((nullableInt->valid[whichBitset].test(bitPosition)) == 1) {
                sumOfValidNums += nullableInt->nums[i];
                validBitsCount++;
            }
        }

        // prevents divide by 0 error
        if (validBitsCount == 0) {
            return {0.0, false};
        }

        return {sumOfValidNums / validBitsCount, true}; 
    }

    DivideResult Divide(const NullableInts* numerator, const NullableInts* denominator) {
        if (numerator == nullptr || denominator == nullptr) {
            return {{}, false}; 
        }

        auto [res, isSameLength] = sparrow::warmup::BitAnd(numerator->valid, denominator->valid);
        if (isSameLength == false) {
            return {{}, false};
        }

        std::vector<int> divisionResult;
        std::vector<std::bitset<32>> validResult(res.size(), std::bitset<32>(0));
        int minSize = std::min(numerator->nums.size(), denominator->nums.size()); // get the min size of the numbers
        // we are going to divide with

        for (int i = 0; i < minSize; i++) {
            int bitPosition = i % 32;
            int whichBitset = i / 32;

            if (res[whichBitset].test(bitPosition) == 1) {
                    // also no need to worry about division by 0 error, since we have drop zero 
                    // which takes care of this in our p2 program
                    divisionResult.push_back(numerator->nums[i] / denominator->nums[i]);
                    validResult[whichBitset].set(bitPosition);
            } else {
                divisionResult.push_back(0);
            }

        }
        NullableInts value_result; // matching the valid within DivideResult struct
        value_result.nums = std::move(divisionResult);
        value_result.valid = std::move(validResult);
        return {value_result, true};

    }

    // p3

    // overload
    AverageResult Average(const NullableInts& nullableInt) {
        return Average(&nullableInt);
    }

    NullableInts* StrsToNullableInts(std::vector<std::string> inputs) {

        // adjusting to "inputs" values
        NullableInts* strsToNullableInts = new NullableInts; // allocating heap
        strsToNullableInts->nums.resize(inputs.size());
        strsToNullableInts->valid.resize((inputs.size() + 31) / 32);

        for (size_t i = 0; i < inputs.size(); i++) {
            if (inputs[i] == "null") {
                strsToNullableInts->nums[i] = 0; // default to 0 for null
                strsToNullableInts->valid[i / 32].set(i % 32, false); // sets the bool vals

            // for valid non null values  
            } else {
                strsToNullableInts->nums[i] = std::stoi(inputs[i]); 
                strsToNullableInts->valid[i / 32].set(i % 32, true); // sets the bool vals
            }
        }
        return strsToNullableInts;
    }

    int NullableIntsToArray(const NullableInts& nullableInt, int** array) {
        if (array == nullptr) return 0;  

        int size = 0;
        int arrayIndex = 0;

        for (size_t i = 0; i < nullableInt.nums.size(); i++) {
            if ((nullableInt.valid[i / 32].test(i % 32)) == 1) {
                size++;
            }
        }

        *array = new int[size]; 

        if (*array == nullptr) return 0;
        
        for (size_t i = 0; i < nullableInt.nums.size(); i++) {
            if ((nullableInt.valid[i / 32].test(i % 32)) == 1) {
                (*array)[arrayIndex++] = nullableInt.nums[i];
                
            }
        }

        return size;
    }

    // p4
    IntColumn::IntColumn() {} // empty object
    IntColumn::IntColumn(const std::vector<std::string>& inputs) {
        for (const std::string& str : inputs) {
            if (str != "null") {
                valid.push_back(true);
                nums.push_back(std::stoi(str));

            // invalid for nulls, so we have valid be false and nums be 0, which we will later drop in DropZero
            } else {
                valid.push_back(false);
                nums.push_back(0);
            }
        }
    }

    size_t IntColumn::Size() const {
        return nums.size();
    }

    void IntColumn::DropZero() {
        for (size_t i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                valid[i] = false; // assigns the valid bool vector pos (i) false
            } 
        }
    }

    AverageResult IntColumn::Average() {
        float sum = 0;
        int count = 0;
        for (size_t i = 0; i < nums.size(); i++) {
            if (valid[i]) {
                sum += nums[i];
                count++;
            }
        }
        if (count > 0) {
            return {sum / count, true};
        } else {
            return {0.0, false}; // preventing divide by 0 errors
        }
    }

    // our easier divide function!
    IntColumn IntColumn::operator/(const IntColumn& other) {
        IntColumn result;

        size_t minSize = std::min(nums.size(), other.nums.size());
        // similar to how we did         
        // int minSize = std::min(numerator->nums.size(), denominator->nums.size());

        for (size_t i = 0; i < minSize; i++) {
            if (valid[i] && other.valid[i] && other.nums[i] != 0) {
                result.valid.push_back(true);
                result.nums.push_back(nums[i] / other.nums[i]);
            } else {
                result.valid.push_back(false);
                result.nums.push_back(0);
            }
        }
        return result;
    }

    // indexing
    const int* IntColumn::operator[](int idx) {

        // ex) if we had index -1 but then add the size to it, it will correspond
        // to last number
        if (idx < 0) {
            idx += Size(); // this adjusts negative index
        }

        // if our index is greater than size or our index element is null
        if (valid[idx] == false || idx >= Size()) {
            return nullptr;
        }

        return &nums[idx];
    }

    std::ostream& operator<<(std::ostream& os, const IntColumn& col) {
    os << "IntColumn:\n";
    for (size_t i = 0; i < col.nums.size(); ++i) {
        if (col.valid[i]) {
            os << col.nums[i] << "\n";
        } else {
            os << "null\n";
        }
    }
    return os;
    }

    NamedIntColumn::NamedIntColumn(const std::string& name, const std::vector<std::string>& inputs)
    : name(name), col(std::make_unique<IntColumn>(inputs)) {}

    NamedIntColumn::NamedIntColumn(const std::string& name, std::unique_ptr<IntColumn> col)
        : name(name), col(std::move(col)) {}  // New constructor definition

    NamedIntColumn::NamedIntColumn(const NamedIntColumn& other)
        : name(other.name), col(std::make_unique<IntColumn>(*other.col)) {}

    NamedIntColumn::NamedIntColumn(NamedIntColumn&& other) noexcept
        : name(std::move(other.name)), col(std::move(other.col)) {
        other.name.clear();
        other.col.reset();
    }

    NamedIntColumn& NamedIntColumn::operator=(const NamedIntColumn& other) {
        if (this == &other) {
            return *this; // Handle self-assignment
        }
        name = other.name;
        col = std::make_unique<IntColumn>(*other.col);
        return *this;
    }

    NamedIntColumn& NamedIntColumn::operator=(NamedIntColumn&& other) noexcept {
        if (this != &other) {
            col.reset();
            name = std::move(other.name);
            col = std::move(other.col);
            other.name.clear();
            other.col.reset();
        }
        return *this;
    }

    NamedIntColumn NamedIntColumn::operator/(const NamedIntColumn& other) const {
        std::unique_ptr<IntColumn> resultCol = std::make_unique<IntColumn>(*col / *other.col);
        return NamedIntColumn(name + "/" + other.name, std::move(resultCol));
    }

    NamedIntColumn NamedIntColumn::operator/(int scalar) const {
        std::unique_ptr<IntColumn> resultCol = std::make_unique<IntColumn>(*col / scalar);
        return NamedIntColumn(name + "/" + std::to_string(scalar), std::move(resultCol));

    }

    IntColumn IntColumn::operator/(int scalar) {
        IntColumn result;
        for (size_t i = 0; i < nums.size(); i++) {
            if (valid[i] && scalar != 0) {
                result.valid.push_back(true);
                result.nums.push_back(nums[i] / scalar);
            } else {
                result.valid.push_back(false);
                result.nums.push_back(0);
            }
        }
        return result;
    }
    

    Table::Table(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        size_t numRows, numCols;
        file >> numRows >> numCols;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// skipping new line

        for (size_t col = 0; col < numCols; ++col) {
            std::string colName;
            std::getline(file, colName);

            std::vector<std::string> values;
            for (size_t row = 0; row < numRows; ++row) {
                std::string value;
                std::getline(file, value);
                values.push_back(value);
            }

            AddCol(NamedIntColumn(colName, values));
        }
    }

    void Table::AddCol(const NamedIntColumn& col) {
        columns.emplace_back(col.name, std::make_shared<NamedIntColumn>(col));
    }

    void Table::AddCol(std::shared_ptr<NamedIntColumn> col) {
        columns.emplace_back(col->name, col);
    }

    std::shared_ptr<NamedIntColumn> Table::operator[](const std::string& colName) const {
        for (const auto& pair : columns) {
            if (pair.first == colName) {
                return pair.second;
            }
        }
        return nullptr;  // Return nullptr if the column not found
    }

    std::ostream& operator<<(std::ostream& os, const Table& table) {
        // Print the column headers
        bool first = true;
        for (const auto& [name, colPtr] : table.columns) {
            if (!first) {
                os << ",";
            }
            os << name;
            first = false;
        }
        os << "\n";

        size_t numRows = 0;
        for (const auto& [name, colPtr] : table.columns) {
            if (colPtr->col) {
                numRows = std::max(numRows, colPtr->col->Size());
            }
        }

        for (size_t row = 0; row < numRows; ++row) {
            first = true;
            for (const auto& [name, colPtr] : table.columns) {
                if (!first) {
                    os << ",";
                }
                const int* value = (*colPtr->col)[static_cast<int>(row)];
                if (value) {
                    os << *value;
                } else {
                    os << "null";
                }
                first = false;
            }
            os << "\n";
        }
        return os;
    }
   
}
