#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include <vector>
#include <map>

class GameEngine {
private:
    std::string currentRoom;
    std::map<std::string, std::string> roomDescriptions;
    std::map<std::string, std::map<std::string, std::string>> roomExits; // Room -> (Direction -> Next Room)

public:
    GameEngine();
    void loadGameData(const std::map<std::string, std::string>& descriptions,
                        const std::map<std::string, std::map<std::string, std::string>>& exits);
    std::string getCurrentRoom() const;
    std::string getDescription() const;
    std::string move(const std::string& direction);
};

#endif