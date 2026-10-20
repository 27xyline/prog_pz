#include "DynamicArray.h"

#include <algorithm>
#include <ostream>
#include <stdexcept>

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

int DynamicArray::get(size_t index) const {
    if (index >= size_) {
        throw out_of_range("DynamicArray index is out of range");
    }
    return data_[index];
}

void DynamicArray::set(size_t index, int value) {
    if (index >= size_) {
        throw out_of_range("DynamicArray index is out of range");
    }
    validate_value(value);
    data_[index] = value;
}

void DynamicArray::push_back(int value) {
    validate_value(value);

    int* expanded = new int[size_ + 1];
    if (size_ != 0) {
        copy(data_, data_ + size_, expanded);
    }
    expanded[size_] = value;

    delete[] data_;
    data_ = expanded;
    ++size_;
}

void DynamicArray::add(const DynamicArray& other) {
    combine(other, 1);
}

void DynamicArray::subtract(const DynamicArray& other) {
    combine(other, -1);
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

void DynamicArray::validate_value(int value) {
    if (value < -100 or value > 100) {
        throw invalid_argument("DynamicArray values must be in [-100, 100]");
    }
}

void DynamicArray::combine(const DynamicArray& other, int sign) {
    const size_t shared_size = min(size_, other.size_);

    for (size_t i = 0; i < size_; ++i) {
        const int right = i < shared_size ? other.data_[i] : 0;
        const int result = data_[i] + sign * right;
        validate_value(result);
    }

    for (size_t i = 0; i < size_; ++i) {
        const int right = i < shared_size ? other.data_[i] : 0;
        data_[i] += sign * right;
    }
}
