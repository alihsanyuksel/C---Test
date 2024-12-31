#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

// Function to generate a random string of given length
std::string generateRandomString(int length) {
    std::string str = "";
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, sizeof(alphanum) - 2); // -2 to exclude null terminator

    for (int i = 0; i < length; ++i) {
        str += alphanum[distrib(gen)];
    }
    return str;
}

// Function to generate a random integer within a given range
int generateRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

// Example function to be tested (replace with your actual function)
int add(int a, int b) {
    return a + b;
}

int main() {
    int numTestCases = 10; // Number of test cases to generate

    std::cout << "// Test cases for the add function\n";
    std::cout << "#include \"gtest/gtest.h\"\n\n"; // Include gtest header

    for (int i = 0; i < numTestCases; ++i) {
        int a = generateRandomInt(-100, 100); // Generate random input a
        int b = generateRandomInt(-100, 100); // Generate random input b
        int expectedResult = add(a, b);       // Calculate the expected result

        std::cout << "TEST(AddTest, Test" << i << ") {\n";
        std::cout << "  EXPECT_EQ(" << expectedResult << ", add(" << a << ", " << b << "));\n";
        std::cout << "}\n\n";
    }

    // Example of string test case generation
    std::cout << "// Example string test\n";
    std::string testString = generateRandomString(generateRandomInt(5, 20));
    std::cout << "TEST(StringTest, RandomString) {\n";
    std::cout << "  std::string str = \"" << testString << "\";\n";
    std::cout << "  EXPECT_EQ(" << testString.length() << ", str.length());\n";
    std::cout << "}\n";

    return 0;
}