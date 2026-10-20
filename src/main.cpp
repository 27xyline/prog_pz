#include "DynamicArray.h"

#include <iostream>
#include <new>
#include <stdexcept>

using namespace std;

int main() {
    DynamicArray numbers(3);
    numbers.set(0, 10);
    numbers.set(1, -4);
    numbers.set(2, 7);

    cout << "numbers: ";
    numbers.print(cout);
    cout << '\n';

    DynamicArray copied(numbers);
    copied.set(0, 20);
    cout << "numbers after changing the copy: ";
    numbers.print(cout);
    cout << '\n';
    cout << "copied: ";
    copied.print(cout);
    cout << '\n';

    numbers.push_back(5);
    cout << "after push_back: ";
    numbers.print(cout);
    cout << '\n';

    DynamicArray shorter(2);
    shorter.set(0, 3);
    shorter.set(1, 2);

    numbers.add(shorter);
    cout << "after add: ";
    numbers.print(cout);
    cout << '\n';

    numbers.subtract(shorter);
    cout << "after subtract: ";
    numbers.print(cout);
    cout << '\n';

    cout << "element at index 1: " << numbers.get(1) << '\n';
    cout << "size: " << numbers.size() << '\n';

    try {
        numbers.get(numbers.size());
        cerr << "ERROR: get did not throw out_of_range\n";
        return 1;
    } catch (const out_of_range& error) {
        cout << "Caught out_of_range: " << error.what() << '\n';
    }

    try {
        numbers.set(numbers.size(), 0);
        cerr << "ERROR: set did not throw out_of_range\n";
        return 1;
    } catch (const out_of_range& error) {
        cout << "Caught out_of_range in set: " << error.what() << '\n';
    }

    try {
        numbers.set(0, 101);
        cerr << "ERROR: set did not throw invalid_argument\n";
        return 1;
    } catch (const invalid_argument& error) {
        cout << "Caught invalid_argument for an invalid value: "
             << error.what() << '\n';
    }

    try {
        numbers.push_back(101);
        cerr << "ERROR: push_back did not throw invalid_argument\n";
        return 1;
    } catch (const invalid_argument& error) {
        cout << "Caught invalid_argument in push_back: "
             << error.what() << '\n';
    }

    DynamicArray maximum(1);
    DynamicArray increment(1);
    maximum.set(0, 100);
    increment.set(0, 1);
    try {
        maximum.add(increment);
        cerr << "ERROR: add did not throw invalid_argument\n";
        return 1;
    } catch (const invalid_argument& error) {
        cout << "Caught invalid_argument for an invalid sum: "
             << error.what() << '\n';
        cout << "maximum after rejected addition: ";
        maximum.print(cout);
        cout << '\n';
    }

    try {
        throw bad_alloc();
    } catch (const bad_alloc& error) {
        cout << "Caught simulated bad_alloc: " << error.what() << '\n';
    }
}
