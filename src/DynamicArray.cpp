#include "DynamicArray.h"

#include <algorithm>
#include <ostream>

using namespace std;

DynamicArray::DynamicArray(size_t size)
    : data_(size == 0 ? nullptr : new int[size]()), size_(size) {}

DynamicArray::DynamicArray(const DynamicArray& other)
    : data_(other.size_ == 0 ? nullptr : new int[other.size_]),
      size_(other.size_) {
    if (size_ != 0) {
        copy(other.data_, other.data_ + size_, data_);
    }
}

DynamicArray::~DynamicArray() {
    delete[] data_;
}

size_t DynamicArray::size() const noexcept {
    return size_;
}

bool DynamicArray::get(size_t index, int& value) const {
    if (index >= size_) {
        return false;
    }
    value = data_[index];
    return true;
}

bool DynamicArray::set(size_t index, int value) {
    if (index >= size_ or !is_valid_value(value)) {
        return false;
    }
    data_[index] = value;
    return true;
}

bool DynamicArray::push_back(int value) {
    if (!is_valid_value(value)) {
        return false;
    }

    int* expanded = new int[size_ + 1];
    if (size_ != 0) {
        copy(data_, data_ + size_, expanded);
    }
    expanded[size_] = value;

    delete[] data_;
    data_ = expanded;
    ++size_;
    return true;
}

bool DynamicArray::add(const DynamicArray& other) {
    return combine(other, 1);
}

bool DynamicArray::subtract(const DynamicArray& other) {
    return combine(other, -1);
}

void DynamicArray::print(ostream& output) const {
    output << '[';
    for (size_t i = 0; i < size_; ++i) {
        if (i != 0) {
            output << ", ";
        }
        output << data_[i];
    }
    output << ']';
}

bool DynamicArray::is_valid_value(int value) noexcept {
    return value >= -100 and value <= 100;
}

bool DynamicArray::combine(const DynamicArray& other, int sign) {
    const size_t shared_size = min(size_, other.size_);

    for (size_t i = 0; i < size_; ++i) {
        const int right = i < shared_size ? other.data_[i] : 0;
        const int result = data_[i] + sign * right;
        if (!is_valid_value(result)) {
            return false;
        }
    }

    for (size_t i = 0; i < size_; ++i) {
        const int right = i < shared_size ? other.data_[i] : 0;
        data_[i] += sign * right;
    }
    return true;
}
