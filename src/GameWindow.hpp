#pragma once
#include <map>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "Map.hpp"
#include "Player.hpp"

class GameWindow
{
private:
    sf::Texture mapTexture;
    sf::Texture playerTexture;
    Player player = Player(playerTexture);
    std::map<std::string, Map> namedMaps;
    Map* currentMap;
    void changeMap(std::string newMap);
public:
    GameWindow(std::filesystem::path resourceFolderPath);
    void draw();
};

