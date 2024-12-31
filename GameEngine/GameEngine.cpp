#include "GameEngine.h"

GameEngine::GameEngine() : currentRoom("") {}

void GameEngine::loadGameData(const std::map<std::string, std::string>& descriptions,
                               const std::map<std::string, std::map<std::string, std::string>>& exits) {
    roomDescriptions = descriptions;
    roomExits = exits;
    if (!roomDescriptions.empty()) {
        currentRoom = roomDescriptions.begin()->first; // Set initial room
    }
}

std::string GameEngine::getCurrentRoom() const {
    return currentRoom;
}

std::string GameEngine::getDescription() const {
    if (roomDescriptions.count(currentRoom)) {
        return roomDescriptions.at(currentRoom);
    }
    return "Unknown room.";
}

std::string GameEngine::move(const std::string& direction) {
    if (roomExits.count(currentRoom) && roomExits.at(currentRoom).count(direction)) {
        currentRoom = roomExits.at(currentRoom).at(direction);
        return getDescription();
    }
    return "You can't go that way.";
}