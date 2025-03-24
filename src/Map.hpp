#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include <nlohmann/json.hpp>

#include "Player.hpp"
#include "Teleport.hpp"
#include "ColisionResult.hpp"

class Map
{
private:
    sf::Sprite sprite;
    sf::Text textName;
    std::vector<sf::FloatRect> walls;
    std::vector<Teleport> teleporters;
    std::string name;
    std::string north;
    std::string east;
    std::string south;
    std::string west;
    Rotation upDirection{Rotation::NORTH};
    Rotation screenExitDirection;

    static sf::Texture dummy;
    static sf::Font font;


public:
    static sf::FloatRect rotateAroundCenter(sf::FloatRect original, Rotation upDirection);
    // invalid not to be used
    Map();
    Map(nlohmann::json& data, sf::Texture& texture);
    // if player colides with wall it gets moved out again
    // returns name of new map on exit
    ColisionResult colide(Player& player);
    const std::string& getName() const;
    Rotation getRotation() const;
    void enter(Rotation inDirection, const std::string& inName);
    void draw(sf::RenderWindow& window) const;
    Rotation getExitDirection() const;
    void arrive(Rotation myUp);
};
