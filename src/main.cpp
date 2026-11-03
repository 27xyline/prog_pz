#include "DynamicArray.h"

#include <iostream>
#include <new>
#include <stdexcept>
#include <string>

using namespace std;

int main() {
    DynamicArray<int> first(3);
    first.set(0, 3);
    first.set(1, 4);
    first.set(2, 0);

    DynamicArray<int> second(3);
    second.set(0, 0);
    second.set(1, 0);
    second.set(2, 12);

    cout << "Integer array: " << first << '\n';
    cout << "Distance between integer arrays: "
         << first.distance_to(second) << '\n';

    DynamicArray<double> decimals(2);
    decimals.set(0, 1.5);
    decimals.set(1, 2.5);
    cout << "Decimal array: " << decimals << '\n';

    DynamicArray<string> words(2);
    words.set(0, "hello");
    words.set(1, "world");
    words.push_back("!");
    cout << "String array: " << words << '\n';

    try {
        words.distance_to(words);
        cerr << "ERROR: distance for strings did not throw bad_typeid\n";
        return 1;
    } catch (const bad_typeid& error) {
        cout << "Caught bad_typeid for string arrays: " << error.what() << '\n';
    }

    try {
        DynamicArray<int> shorter(2);
        first.distance_to(shorter);
        cerr << "ERROR: different sizes did not throw invalid_argument\n";
        return 1;
    } catch (const invalid_argument& error) {
        cout << "Caught invalid_argument for different sizes: "
             << error.what() << '\n';
    }

    try {
        first.set(0, 101);
        cerr << "ERROR: invalid integer did not throw invalid_argument\n";
        return 1;
    } catch (const invalid_argument& error) {
        cout << "Caught invalid_argument for integer value: "
             << error.what() << '\n';
    }

    try {
        first.get(first.size());
        cerr << "ERROR: invalid index did not throw out_of_range\n";
        return 1;
    } catch (const out_of_range& error) {
        cout << "Caught out_of_range: " << error.what() << '\n';
    }

    try {
        throw bad_alloc();
    } catch (const bad_alloc& error) {
        cout << "Caught simulated bad_alloc: " << error.what() << '\n';
    }
}
