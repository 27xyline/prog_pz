#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cstddef>
#include <iosfwd>

using namespace std;

class DynamicArray {
public:
    explicit DynamicArray(size_t size);
    DynamicArray(const DynamicArray& other);
    ~DynamicArray();

    DynamicArray& operator=(const DynamicArray& other) = delete;

    size_t size() const noexcept;
    int get(size_t index) const;
    void set(size_t index, int value);
    void push_back(int value);

    void add(const DynamicArray& other);
    void subtract(const DynamicArray& other);

    void print(ostream& output) const;

private:
    int* data_;
    size_t size_;

    static void validate_value(int value);
    void combine(const DynamicArray& other, int sign);
};

#endif
