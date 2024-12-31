#include <gtest/gtest.h>
#include "char.h"

TEST(CharacterTest, Initialization) {
    Character character("Hero", 100, 10, 5);
    EXPECT_EQ(character.getName(), "Hero");
    EXPECT_EQ(character.getHealth(), 100);
    EXPECT_EQ(character.getStrength(), 10);
    EXPECT_EQ(character.getDexterity(), 5);
}

TEST(CharacterTest, TakeDamage) {
    Character character("Hero", 100, 10, 5);
    character.takeDamage(20);
    EXPECT_EQ(character.getHealth(), 80);
}

TEST(CharacterTest, Attack) {
    Character attacker("Attacker", 100, 15, 5);
    Character defender("Defender", 100, 10, 5);

    attacker.attack(defender);
    EXPECT_EQ(defender.getHealth(), 85);
}

TEST(CharacterTest, IncreaseDexterity) {
    Character character("Rogue", 80, 8, 12);
    character.increaseDexterity(3);
    EXPECT_EQ(character.getDexterity(), 15);
}

TEST(CharacterTest, IncreaseDexterityInvalidInput) {
    Character character("Rogue", 80, 8, 12);
    EXPECT_THROW(character.increaseDexterity(-3), std::invalid_argument);
    EXPECT_THROW(character.increaseDexterity(0), std::invalid_argument);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}