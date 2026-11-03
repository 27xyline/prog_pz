#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>

using namespace std;

template <typename T = int>
class DynamicArray {
public:
    explicit DynamicArray(size_t size)
        : data_(size == 0 ? nullptr : new T[size]()), size_(size) {}

    DynamicArray(const DynamicArray& other)
        : data_(other.size_ == 0 ? nullptr : new T[other.size_]),
          size_(other.size_) {
        try {
            if (size_ != 0) {
                copy(other.data_, other.data_ + size_, data_);
            }
        } catch (...) {
            delete[] data_;
            throw;
        }
    }

    ~DynamicArray() {
        delete[] data_;
    }

    DynamicArray& operator=(const DynamicArray& other) = delete;

    size_t size() const noexcept {
        return size_;
    }

    T get(size_t index) const {
        if (index >= size_) {
            throw out_of_range("DynamicArray index is out of range");
        }
        return data_[index];
    }

    void set(size_t index, const T& value) {
        if (index >= size_) {
            throw out_of_range("DynamicArray index is out of range");
        }
        validate_value(value);
        data_[index] = value;
    }

    void push_back(const T& value) {
        validate_value(value);

        unique_ptr<T[]> expanded(new T[size_ + 1]);
        if (size_ != 0) {
            copy(data_, data_ + size_, expanded.get());
        }
        expanded[size_] = value;

        delete[] data_;
        data_ = expanded.release();
        ++size_;
    }

    void add(const DynamicArray& other) {
        combine(other, 1);
    }

    void subtract(const DynamicArray& other) {
        combine(other, -1);
    }

    void print(ostream& output) const {
        output << '[';
        for (size_t i = 0; i < size_; ++i) {
            if (i != 0) {
                output << ", ";
            }
            output << data_[i];
        }
        output << ']';
    }

    double distance_to(const DynamicArray& other) const {
        if constexpr (!is_arithmetic_v<T>) {
            throw bad_typeid();
        } else {
            if (size_ != other.size_) {
                throw invalid_argument("DynamicArray sizes must match to calculate distance");
            }

            long double sum = 0;
            for (size_t i = 0; i < size_; ++i) {
                const long double difference = static_cast<long double>(data_[i])
                    - static_cast<long double>(other.data_[i]);
                sum += difference * difference;
            }
            return static_cast<double>(sqrt(sum));
        }
    }

private:
    T* data_;
    size_t size_;

    static void validate_value(const T& value) {
        if constexpr (is_integral_v<T>) {
            if constexpr (is_signed_v<T>) {
                if (value < -100 or value > 100) {
                    throw invalid_argument("Integer values must be in [-100, 100]");
                }
            } else if (value > 100) {
                throw invalid_argument("Integer values must be in [-100, 100]");
            }
        }
    }

    void combine(const DynamicArray& other, int sign) {
        if constexpr (!is_arithmetic_v<T>) {
            throw bad_typeid();
        } else {
            const size_t shared_size = min(size_, other.size_);

            for (size_t i = 0; i < size_; ++i) {
                const T right = i < shared_size ? other.data_[i] : T{};
                const T result = sign == 1 ? data_[i] + right : data_[i] - right;
                validate_value(result);
            }

            for (size_t i = 0; i < size_; ++i) {
                const T right = i < shared_size ? other.data_[i] : T{};
                if (sign == 1) {
                    data_[i] += right;
                } else {
                    data_[i] -= right;
                }
            }
        }
    }
};

template <typename T>
ostream& operator<<(ostream& output, const DynamicArray<T>& array) {
    array.print(output);
    return output;
}

#endif
