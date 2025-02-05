#include "gtest/gtest.h"
#include "GameEngine.h"

class GameEngineTest : public ::testing::Test {
protected:
    GameEngine engine;
    std::map<std::string, std::string> descriptions;
    std::map<std::string, std::map<std::string, std::string>> exits;

    void SetUp() override {
        descriptions = {
            {"start", "You are in a starting room."},
            {"hall", "You are in a long hall."},
            {"end", "You have reached the end."}
        };

        exits = {
            {"start", {{"north", "hall"}}},
            {"hall", {{"south", "start"}, {"east", "end"}}}
        };
        engine.loadGameData(descriptions, exits);
    }
};

TEST_F(GameEngineTest, LoadGameData) {
    ASSERT_EQ(engine.getCurrentRoom(), "start");
}

TEST_F(GameEngineTest, LoadEmptyGameData) {
    GameEngine emptyEngine;
    std::map<std::string, std::string> emptyDescriptions;
    std::map<std::string, std::map<std::string, std::string>> emptyExits;
    emptyEngine.loadGameData(emptyDescriptions, emptyExits);
    ASSERT_EQ(emptyEngine.getCurrentRoom(), "");
}

TEST_F(GameEngineTest, GetDescription) {
    ASSERT_EQ(engine.getDescription(), "You are in a starting room.");
    engine.move("north");
    ASSERT_EQ(engine.getDescription(), "You are in a long hall.");
}

TEST_F(GameEngineTest, GetDescriptionNonExistentRoom) {
    std::map<std::string, std::string> badDescriptions = {{"badroom", "This room is bad"}};
    std::map<std::string, std::map<std::string, std::string>> badExits;
    GameEngine badEngine;
    badEngine.loadGameData(badDescriptions, badExits);
    badEngine.move("nowhere");
    ASSERT_EQ(badEngine.getDescription(), "Unknown room.");
}

TEST_F(GameEngineTest, MoveValid) {
    ASSERT_EQ(engine.getCurrentRoom(), "start");
    engine.move("north");
    ASSERT_EQ(engine.getCurrentRoom(), "hall");
}

TEST_F(GameEngineTest, MoveInvalid) {
    ASSERT_EQ(engine.move("east"), "You can't go that way.");
    ASSERT_EQ(engine.getCurrentRoom(), "start"); // Current room should not change
}

TEST_F(GameEngineTest, MoveFromRoomWithNoExits){
    std::map<std::string, std::string> oneRoomDescriptions = {{"room", "This is the only room"}};
    std::map<std::string, std::map<std::string, std::string>> oneRoomExits;
    GameEngine oneRoomEngine;
    oneRoomEngine.loadGameData(oneRoomDescriptions, oneRoomExits);
    ASSERT_EQ(oneRoomEngine.move("anywhere"), "You can't go that way.");
    ASSERT_EQ(oneRoomEngine.getCurrentRoom(), "room");
}

TEST_F(GameEngineTest, MultipleMoves) {
    engine.move("north");
    engine.move("east");
    ASSERT_EQ(engine.getCurrentRoom(), "end");
    engine.move("south");
    ASSERT_EQ(engine.getCurrentRoom(), "end");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}