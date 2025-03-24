#include "Teleport.hpp"

Teleport::Teleport(nlohmann::json& json) {
    if (json["effect"] == "none") {
        effect = NONE;
    }
    else if (json["effrct"] == "keepRotation") {
        effect = KEEP_ROTATION;
    }
    else {
        // TODO: error handle please
    }
    auto target = json["target"];
    targetName = target["map"];
    targetPosition = {target["x"], target["y"]};
    auto origin = json["origin"];
    position = {origin["x"], origin["y"]};
}

bool Teleport::touch(sf::FloatRect pPos) const {
    auto minx = pPos.position.x;
    auto maxx = pPos.position.x + pPos.size.x;
    auto miny = pPos.position.y;
    auto maxy = pPos.position.y + pPos.size.y;
    return position.x <= maxx && position.x >= minx && position.y <= maxy && position.y >= miny;
}

sf::Vector2f Teleport::getTargetPosition() const {
    return targetPosition;
}

const std::string& Teleport::getTargetName() const {
    return targetName;
}

Teleport::Effect Teleport::getEffect() const {
    return effect;
}
