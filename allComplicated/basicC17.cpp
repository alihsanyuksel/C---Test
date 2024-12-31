#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <any>
#include <algorithm>
#include <numeric>
#include <execution> // Include for std::execution

// Using structured bindings for cleaner tuple/pair access
struct Point { double x; double y; };

// Using if constexpr for compile-time branching
template <typename T>
auto print_type_info(const T& val) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Value is an integer: " << val << "\n";
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "Value is a floating-point number: " << val << "\n";
    } else {
        std::cout << "Value is of another type.\n";
    }
}

// Using std::optional to handle potential absence of a value
std::optional<int> find_value(const std::vector<int>& data, int target) {
    for (int val : data) {
        if (val == target) {
            return val;
        }
    }
    return std::nullopt;
}

// Using std::variant to hold different types in a type-safe way
using DataValue = std::variant<int, double, std::string>;

void process_data(const DataValue& data) {
    std::visit([](const auto& val) {
        print_type_info(val);
    }, data);
}

// Using std::any to hold any type (with runtime type checking)
void process_any(const std::any& a) {
    if (a.type() == typeid(int)) {
        std::cout << "Any contains an integer: " << std::any_cast<int>(a) << "\n";
    } else if (a.type() == typeid(std::string)) {
        std::cout << "Any contains a string: " << std::any_cast<std::string>(a) << "\n";
    } else {
        std::cout << "Any contains an unknown type.\n";
    }
}

int main() {
    // Structured bindings example
    Point p{3.0, 4.0};
    auto [x, y] = p; // Decomposes the struct
    std::cout << "Point: x=" << x << ", y=" << y << "\n";

    // if constexpr example
    print_type_info(5);
    print_type_info(3.14);

    // std::optional example
    std::vector<int> numbers = {1, 5, 10, 15};
    if (auto found = find_value(numbers, 10)) {
        std::cout << "Found value: " << *found << "\n";
    } else {
        std::cout << "Value not found.\n";
    }

    if (auto not_found = find_value(numbers, 20)) {
        std::cout << "Found value: " << *not_found << "\n";
    } else {
        std::cout << "Value not found.\n";
    }

    // std::variant example
    DataValue dv1 = 42;
    DataValue dv2 = 3.14159;
    DataValue dv3 = "Hello C++17";
    process_data(dv1);
    process_data(dv2);
    process_data(dv3);

    // std::any example
    std::any a1 = 123;
    std::any a2 = std::string("Any value");
    process_any(a1);
    process_any(a2);


    // Example with std::reduce (C++17 parallel algorithms)
    std::vector<int> large_numbers(1000000);
    std::iota(large_numbers.begin(), large_numbers.end(), 1); // Fill with 1, 2, 3...

    // Summing the vector (using execution policies for potential parallelism)
    long long sum = std::reduce(std::execution::par, large_numbers.begin(), large_numbers.end(), 0LL);
    std::cout << "Sum of large numbers (parallel): " << sum << "\n";

    return 0;
}