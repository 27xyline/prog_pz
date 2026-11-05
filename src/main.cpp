#include "DynamicArray.h"

#include <iostream>
#include <new>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std;

void print_by_value(DynamicArray<int> values) {
    cout << "Function received: " << values << '\n';
}

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

    DynamicArray<int> operators_array(3);
    operators_array[0] = 10;
    operators_array[1] = -4;
    operators_array[2] = 7;

    DynamicArray<int> operators_other(2);
    operators_other[0] = 3;
    operators_other[1] = 2;

    cout << "operator[] read: " << static_cast<int>(operators_array[1]) << '\n';
    DynamicArray<int> operators_copy(operators_array);
    cout << "equal to its copy: " << (operators_array == operators_copy) << '\n';
    cout << "different from shorter array: "
         << (operators_array != operators_other) << '\n';

    operators_array += operators_other;
    cout << "after array +=: " << operators_array << '\n';
    operators_array -= operators_other;
    cout << "after array -=: " << operators_array << '\n';

    operators_array += 2;
    cout << "after scalar +=: " << operators_array << '\n';
    operators_array -= 2;
    cout << "after scalar -=: " << operators_array << '\n';

    for (auto& value : operators_array) {
        value += 1;
    }
    cout << "after mutable range-for: " << operators_array << '\n';

    const DynamicArray<int>& read_only_array = operators_array;
    cout << "const range-for:";
    for (const auto& value : read_only_array) {
        cout << ' ' << value;
    }
    cout << '\n';

    try {
        operators_array[operators_array.size()] = 0;
        cerr << "ERROR: operator[] did not throw out_of_range\n";
        return 1;
    } catch (const out_of_range& error) {
        cout << "Caught out_of_range from operator[]: " << error.what() << '\n';
    }

    try {
        operators_array[0] = 101;
        cerr << "ERROR: operator[] did not validate the value\n";
        return 1;
    } catch (const invalid_argument& error) {
        cout << "Caught invalid_argument from operator[]: " << error.what() << '\n';
    }

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

    DynamicArray<int> copy_source(3);
    copy_source.set(0, 8);
    copy_source.set(1, 9);
    copy_source.set(2, 10);

    DynamicArray<int> copy_assigned(1);
    copy_assigned = copy_source;
    cout << "After copy assignment: " << copy_assigned << '\n';

    DynamicArray<int>& same_copy_object = copy_assigned;
    copy_assigned = same_copy_object;
    cout << "After self-copy assignment: " << copy_assigned << '\n';

    DynamicArray<int> move_constructor_source(2);
    move_constructor_source.set(0, 20);
    move_constructor_source.set(1, 30);
    DynamicArray<int> move_constructed(std::move(move_constructor_source));
    cout << "Move constructor destination: " << move_constructed << '\n';
    cout << "Move constructor source size: " << move_constructor_source.size() << '\n';

    DynamicArray<int> move_assignment_source(2);
    move_assignment_source.set(0, 40);
    move_assignment_source.set(1, 50);
    DynamicArray<int> move_assigned(1);
    move_assigned.set(0, -1);
    move_assigned = std::move(move_assignment_source);
    cout << "Move assignment destination: " << move_assigned << '\n';
    cout << "Move assignment source size: " << move_assignment_source.size() << '\n';

    DynamicArray<int>& same_move_object = move_assigned;
    move_assigned = std::move(same_move_object);
    cout << "After self-move assignment: " << move_assigned << '\n';

    cout << "Passing an lvalue by value (copy):\n";
    print_by_value(copy_source);
    cout << "Original after copy: " << copy_source << '\n';

    cout << "Passing an rvalue by value (move):\n";
    print_by_value(std::move(copy_source));
    cout << "Source size after move: " << copy_source.size() << '\n';
}
