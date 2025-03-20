#include "Map.hpp"

#include <print>

using sf::Literals::operator""_deg;

sf::Texture Map::dummy = sf::Texture();
sf::Font Map::font = sf::Font("/usr/share/fonts/truetype/ubuntu/UbuntuMono[wght].ttf");

// chat gpt said
sf::FloatRect Map::rotateAroundCenter(const sf::FloatRect& rect) const {
    float x = rect.position.x, y = rect.position.y, w = rect.size.x, h = rect.size.y;
    float px = 400, py = 400;

    switch (upDirection) {
    case Rotation::EAST:
        return sf::FloatRect({px - (y + h - py), py + (x - px)}, {h, w});  // Swap width and height
    case Rotation::WEST:
        return sf::FloatRect({px + (y - py), py - (x + w - px)}, {h, w});  // Swap width and height
    case Rotation::SOUTH:
        return sf::FloatRect({2 * px - (x + w), 2 * py - (y + h)}, {w, h});
    case Rotation::NORTH:
        return rect;  // No rotation
    }
    std::unreachable();
}

Map::Map() : sprite{dummy}, textName{font} {}

Map::Map(nlohmann::json& data, sf::Texture& texture) : sprite{texture}, textName{font} {
    name = data.at("name");
    north = data["north"];
    east = data["east"];
    south = data["south"];
    west = data["west"];
    textName.setString(name);
    textName.setFillColor(sf::Color::Black);
    sf::IntRect textureCoordinates({data.at("texture").at("x"), data["texture"].at("y")}, {800, 800});
    sprite.setTextureRect(textureCoordinates);
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
    sprite.move({400, 400});
    for (auto& j : data["walls"]) {
        walls.emplace_back(sf::Vector2f{j.at("x"), j.at("y")}, sf::Vector2f{j.at("width"), j.at("height")});
    }
}

std::optional<std::string> Map::colide(Player& player) {
    auto playerPos = player.getPosition();
    std::optional<int> extraRot;
    if (playerPos.position.x < 0) {
        playerPos.position.x = 800 - playerPos.size.x / 2 - .1;
        playerPos.position.y += playerPos.size.y / 2;
        player.setPosition(playerPos.position);
        extraRot = 3;
        screenExitDirection = Rotation::WEST;
    }
    else if (playerPos.position.y < 0) {
        playerPos.position.y = 800 - playerPos.size.y / 2 - .1;
        playerPos.position.x += playerPos.size.x / 2;
        player.setPosition(playerPos.position);
        extraRot = 0;
        screenExitDirection = Rotation::NORTH;
    }
    else if (playerPos.position.x + playerPos.size.x > 800) {
        playerPos.position.x = playerPos.size.x / 2 + .1;
        playerPos.position.y += playerPos.size.y / 2;
        player.setPosition(playerPos.position);
        extraRot = 1;
        screenExitDirection = Rotation::EAST;
    }
    else if (playerPos.position.y + playerPos.size.y > 800) {
        playerPos.position.y = playerPos.size.y / 2 + .1;
        playerPos.position.x += playerPos.size.x / 2;
        player.setPosition(playerPos.position);
        extraRot = 2;
        screenExitDirection = Rotation::SOUTH;
    }
    if (extraRot) {
        switch ((4 - (int)upDirection + *extraRot) % 4) {
        case 0:
            return north;
        case 1:
            return east;
        case 2:
            return south;
        case 3:
            return west;
        }
    }
    for (auto w : walls) {
        auto rotated = rotateAroundCenter(w);

        if (const std::optional i = rotated.findIntersection(playerPos)) {
            switch (player.getFacing()) {
            case Rotation::NORTH:
                if (std::abs(i->size.x) < std::abs(i->size.y)) {
                    continue;
                }
                playerPos.position.y = rotated.position.y + rotated.size.y + playerPos.size.y / 2 + 1;
                playerPos.position.x += playerPos.size.x / 2;
                break;
            case Rotation::EAST:
                if (std::abs(i->size.x) > std::abs(i->size.y)) {
                    continue;
                }
                playerPos.position.x = rotated.position.x - playerPos.size.x / 2 - 1;
                playerPos.position.y += playerPos.size.y / 2;
                break;
            case Rotation::SOUTH:
                if (std::abs(i->size.x) < std::abs(i->size.y)) {
                    continue;
                }
                playerPos.position.y = rotated.position.y - playerPos.size.y / 2 - 1;
                playerPos.position.x += playerPos.size.x / 2;
                break;
            case Rotation::WEST:
                if (std::abs(i->size.x) > std::abs(i->size.y)) {
                    continue;
                }
                playerPos.position.x = rotated.position.x + rotated.size.x + playerPos.size.x / 2 + 1;
                playerPos.position.y += playerPos.size.y / 2;
            }
            player.setPosition(playerPos.position);
        }
    }
    return std::nullopt;
}

const std::string& Map::getName() const {
    return name;
}

Rotation Map::getRotation() const {
    return upDirection;
}

void Map::enter(Rotation inDirection, const std::string& inName) {
    if (inName == north) {
        sprite.setRotation(180_deg);
        upDirection = Rotation::SOUTH;
    }
    else if (inName == east) {
        sprite.setRotation(90_deg);
        upDirection = Rotation::WEST;
    }
    else if (inName == south) {
        sprite.setRotation(0_deg);
        upDirection = Rotation::NORTH;
    }
    else if (inName == west) {
        sprite.setRotation(270_deg);
        upDirection = Rotation::EAST;
    }
    else {
        std::println("{} {}", inName, (int)inDirection);
        exit(255);
    }
    sprite.rotate(sf::degrees(int(inDirection) * 90));
    upDirection = (Rotation)(((int)inDirection + 4 - (int)upDirection) % 4);
}

void Map::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
    window.draw(textName);
}

Rotation Map::getExitDirection() const {
    return screenExitDirection;
}
