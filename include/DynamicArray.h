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
    bool get(size_t index, int& value) const;
    bool set(size_t index, int value);
    bool push_back(int value);

    bool add(const DynamicArray& other);
    bool subtract(const DynamicArray& other);

    void print(ostream& output) const;

private:
    int* data_;
    size_t size_;

    static bool is_valid_value(int value) noexcept;
    bool combine(const DynamicArray& other, int sign);
};

#endif
