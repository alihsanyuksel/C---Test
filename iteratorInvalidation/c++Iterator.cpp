#include <iostream>
#include <vector>
#include <string>

struct User {
    std::string name;
    bool isActive;
    int someData[1000]; // Add some data to make the User struct larger

    User(const std::string& n, bool active) : name(n), isActive(active) {}
};

int main() {
    std::vector<User> users = {
        {"Alice", true},
        {"Bob", false},
        {"Charlie", true},
        {"David", false},
        {"Eve", true},
        {"Frank", false},
        {"Grace", true},
        {"Henry", false}
    };

    // Remove inactive users - PROBLEM!
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (!it->isActive) {
            std::cout << "Removing inactive user: " << it->name << std::endl;
            users.erase(it); // Iterator invalidation!
        }
    }

    // Print remaining users (CRASH OR GARBAGE OUTPUT LIKELY HERE)
    std::cout << "\nActive users:" << std::endl;
    for (const auto& user : users) {
        std::cout << user.name << std::endl;
    }

    return 0;
}