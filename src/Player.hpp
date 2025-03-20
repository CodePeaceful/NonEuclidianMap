#pragma once

#include <SFML/Graphics.hpp>

enum class Rotation
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

// to be moved with arrow keys or wasd
class Player
{
private:
    sf::Sprite sprite;
    Rotation facing{Rotation::NORTH};
public:
    Player(sf::Texture& texture);
    void moveUp();
    void moveLeft();
    void moveDown();
    void moveRight();
    sf::FloatRect getPosition() const;
    void setPosition(sf::Vector2f newPosition);
    void draw(sf::RenderWindow& window) const;
    Rotation getFacing() const;
};
