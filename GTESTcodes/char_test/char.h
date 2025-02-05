// char.h
#ifndef CHAR_H
#define CHAR_H

#include <string>

class Character {
public:
    Character(const std::string& name, int health, int strength, int dexterity);

    std::string getName() const;
    int getHealth() const;
    int getStrength() const;
    int getDexterity() const;
    void increaseDexterity(int amount); // New function
    void takeDamage(int damage);
    int attack(Character& target);
    void setStrength(int strength);
    int defend(int attackDamage);

private:
    std::string name_;
    int health_;
    int strength_;
    int dexterity_;
};

#endif