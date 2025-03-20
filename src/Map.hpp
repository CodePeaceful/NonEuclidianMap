#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include <nlohmann/json.hpp>

#include "Player.hpp"

class Map
{
private:
    sf::Sprite sprite;
    sf::Text textName;
    std::vector<sf::FloatRect> walls;
    std::string name;
    std::string north;
    std::string east;
    std::string south;
    std::string west;
    Rotation upDirection{Rotation::NORTH};
    Rotation screenExitDirection;

    static sf::Texture dummy;
    static sf::Font font;

    sf::FloatRect rotateAroundCenter(const sf::FloatRect& original) const;

public:
    // invalid not to be used
    Map();
    Map(nlohmann::json& data, sf::Texture& texture);
    // if player colides with wall it gets moved out again
    // returns name of new map on exit
    std::optional<std::string> colide(Player& player);
    const std::string& getName() const;
    Rotation getRotation() const;
    void enter(Rotation inDirection, const std::string& inName);
    void draw(sf::RenderWindow& window) const;
    Rotation getExitDirection() const;
};
