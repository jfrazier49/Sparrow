#pragma once// good practice to do this so that it's not defined over and over
#include <bitset>
#include <vector>
#include <unordered_map> // For std::unordered_map

namespace sparrow {
 
    // for P1
    namespace warmup {
        // first CounBits function
        unsigned CountBits(std::bitset<32> bits, unsigned pos, unsigned len);
    
        // overloaded function (2nd one)
        unsigned CountBits(const std::vector<std::bitset<32>>& bitsets);

        // BitAnd function
        std::pair<std::vector<std::bitset<32>>, bool> BitAnd(std::vector<std::bitset<32>> a,
                                                     std::vector<std::bitset<32>> b);

    }

    // p2

    struct NullableInts {
        std::vector<int> nums;
        std::vector<std::bitset<32>> valid;
    };

     void DropZero(NullableInts* nullableInt);

     struct AverageResult {
        float value; 
        bool ok;
    };

    struct DivideResult {
        NullableInts value; 
        bool ok;  
    };
    AverageResult Average(const NullableInts* nullableInt);
    DivideResult Divide(const NullableInts* numerator, const NullableInts* denominator);
    
    // p3
    AverageResult Average(const NullableInts& nullableInt);
    NullableInts* StrsToNullableInts(std::vector<std::string> inputs);
    int NullableIntsToArray(const NullableInts& nullable, int** outputArray);

    // p4
    class IntColumn {

    // our constructor
    private:

        // will be nums and valid, since this is inspired by NullableInt variables
        std::vector<int> nums;
        std::vector<bool> valid;

    public:
        IntColumn();
        IntColumn(const std::vector<std::string>& inputs);  // Pass by reference
         IntColumn(const IntColumn& other) = default;
         IntColumn& operator=(const IntColumn& other) = default;
        void DropZero();
        AverageResult Average();
        IntColumn operator/(const IntColumn& other); // Column-wise division
        IntColumn operator/(int scalar); // Division by scalar
        size_t Size() const;
        const int* operator[](int idx);

        friend std::ostream& operator<<(std::ostream& os, const IntColumn& col);
    };

    // p5
    class NamedIntColumn {
    public:
    std::string name;
    std::unique_ptr<IntColumn> col;

    NamedIntColumn(const std::string& name, const std::vector<std::string>& inputs);
    NamedIntColumn(const std::string& name, std::unique_ptr<IntColumn> col);
    NamedIntColumn(const NamedIntColumn& other); 
    NamedIntColumn(NamedIntColumn&& other) noexcept; 
    NamedIntColumn& operator=(const NamedIntColumn& other); 
    NamedIntColumn& operator=(NamedIntColumn&& other) noexcept; 

    NamedIntColumn operator/(const NamedIntColumn& other) const; 
    NamedIntColumn operator/(int scalar) const; 

    ~NamedIntColumn() = default;
};

    // p6
   class Table {
    public:
    Table() = default;
    Table(const std::string& filename);

    void AddCol(const NamedIntColumn& col);
    void AddCol(std::shared_ptr<NamedIntColumn> col);
    std::shared_ptr<NamedIntColumn> operator[](const std::string& colName) const;

    friend std::ostream& operator<<(std::ostream& os, const Table& table);

    private:
    std::vector<std::pair<std::string, std::shared_ptr<NamedIntColumn>>> columns;
    };
}
