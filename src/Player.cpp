#include "Player.hpp"

using sf::Literals::operator""_deg;
// speeds above 1 may cause problems
const float speed = 5;

Player::Player(sf::Texture& texture) : sprite{texture} {
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
}

void Player::moveUp() {
    facing = Rotation::NORTH;
    sprite.setRotation(0_deg);
    sprite.move({0, -speed});
}

void Player::moveLeft() {
    facing = Rotation::WEST;
    sprite.setRotation(270_deg);
    sprite.move({-speed, 0});
}

void Player::moveDown() {
    facing = Rotation::SOUTH;
    sprite.setRotation(180_deg);
    sprite.move({0, speed});
}

void Player::moveRight() {
    facing = Rotation::EAST;
    sprite.setRotation(90_deg);
    sprite.move({speed, 0});
}

sf::FloatRect Player::getPosition() const {
    return sprite.getGlobalBounds();
}

void Player::setPosition(sf::Vector2f newPosition) {
    sprite.setPosition(newPosition);
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

Rotation Player::getFacing() const {
    return facing;
}
