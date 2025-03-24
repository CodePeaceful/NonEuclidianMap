#pragma once

#include <nlohmann/json.hpp>

#include "Player.hpp"

class Teleport
{
public:
    enum Effect
    {
        NONE,
        KEEP_ROTATION
    };
private:
    Effect effect = NONE;
    sf::Vector2f position;
    sf::Vector2f targetPosition;
    std::string targetName;
public:
    Teleport(nlohmann::json& json);
    bool touch(sf::FloatRect pPos) const;
    sf::Vector2f getTargetPosition() const;
    const std::string& getTargetName() const;
    Effect getEffect() const;
};

