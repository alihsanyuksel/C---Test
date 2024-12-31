// Character.cpp
#include "char.h"
#include <stdexcept> // Make sure to include this for exceptions

Character::Character(const std::string& name, int health, int strength, int dexterity)
    : name_(name), health_(health), strength_(strength), dexterity_(dexterity) {}

std::string Character::getName() const {
    return name_;
}

int Character::getHealth() const {
    return health_;
}

int Character::getStrength() const {
    return strength_;
}

int Character::getDexterity() const {
    return dexterity_;
}

void Character::increaseDexterity(int amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Dexterity increase amount must be positive.");
    }
    dexterity_ += amount;
}

void Character::takeDamage(int damage) {
    health_ -= damage;
}

int Character::attack(Character& target) {
    int damage = strength_;
    target.takeDamage(damage);
    return damage;
}
