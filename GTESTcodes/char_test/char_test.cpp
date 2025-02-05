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
TEST(CharacterTest, SetStrength) {
    Character character("Warrior", 100, 10, 5);
    character.setStrength(15);
    EXPECT_EQ(character.getStrength(), 10); // Error: Expecting 10 instead of 15
}

TEST(CharacterTest, SetStrengthInvalidInput) {
    Character character("Warrior", 100, 10, 5);
    EXPECT_NO_THROW(character.setStrength(-5)); // Error: Expecting no throw, but it should throw
}

TEST(CharacterTest, Defend) {
    Character defender("Defender", 100, 10, 5);
    int damageTaken = defender.defend(10);
    EXPECT_EQ(damageTaken, 10); // Error: Expecting 10 instead of 5
    EXPECT_EQ(defender.getHealth(), 90); // Error: Expecting 90 instead of 95
}

TEST(CharacterTest, DefendWithHighDexterity) {
    Character defender("Defender", 100, 10, 15);
    int damageTaken = defender.defend(10);
    EXPECT_EQ(damageTaken, 0); // Error: Expecting 5 instead of 0
    EXPECT_EQ(defender.getHealth(), 100); // Error: Expecting 95 instead of 100
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
