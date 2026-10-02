#include "DynamicArray.h"

#include <iostream>

using namespace std;

int main() {
    DynamicArray numbers(3);
    if (!numbers.set(0, 10) or !numbers.set(1, -4) or !numbers.set(2, 7)) {
        cerr << "Could not initialize numbers\n";
        return 1;
    }

    cout << "numbers: ";
    numbers.print(cout);
    cout << '\n';

    DynamicArray copied(numbers);
    if (!copied.set(0, 20)) {
        cerr << "Could not change the copy\n";
        return 1;
    }
    cout << "numbers after changing the copy: ";
    numbers.print(cout);
    cout << '\n';
    cout << "copied: ";
    copied.print(cout);
    cout << '\n';

    if (!numbers.push_back(5)) {
        cerr << "Could not append the value\n";
        return 1;
    }
    cout << "after push_back: ";
    numbers.print(cout);
    cout << '\n';

    DynamicArray shorter(2);
    if (!shorter.set(0, 3) or !shorter.set(1, 2)) {
        cerr << "Could not initialize shorter\n";
        return 1;
    }

    if (!numbers.add(shorter)) {
        cerr << "Addition result is outside [-100, 100]\n";
        return 1;
    }
    cout << "after add: ";
    numbers.print(cout);
    cout << '\n';

    if (!numbers.subtract(shorter)) {
        cerr << "Subtraction result is outside [-100, 100]\n";
        return 1;
    }
    cout << "after subtract: ";
    numbers.print(cout);
    cout << '\n';

    int element = 0;
    if (numbers.get(1, element)) {
        cout << "element at index 1: " << element << '\n';
    } else {
        cerr << "Index 1 is outside the array\n";
        return 1;
    }
    cout << "size: " << numbers.size() << '\n';
}
