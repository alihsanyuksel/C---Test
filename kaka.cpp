#include <fstream>
#include <string> // line added after edit for clarity
#include <iostream>

int main() {
    std::string filename = "input.txt";
    std::ifstream in(filename);
    std::cout << filename ;

    return 0;
}