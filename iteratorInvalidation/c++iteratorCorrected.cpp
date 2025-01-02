#include <iostream>
#include <vector>
#include <string>

struct User {
    std::string name;
    bool isActive;
    int someData[1000]; // Make User larger

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

    for (auto it = users.begin(); it != users.end();) { // Correct loop
        if (!it->isActive) {
            std::cout << "Removing inactive user: " << it->name << std::endl;
            it = users.erase(it); // Correct erase
        } else {
            ++it;
        }
    }

    std::cout << "\nActive users:" << std::endl;
    for (const auto& user : users) {
        std::cout << user.name << std::endl;
    }

    return 0;
}