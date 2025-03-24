#include "GameWindow.hpp"

#include <sstream>
#include <fstream>

void GameWindow::changeMap(std::string newMap) {
    Map* map = &namedMaps[newMap];
    map->enter(currentMap->getExitDirection(), currentMap->getName());
    currentMap = map;
}

GameWindow::GameWindow(std::filesystem::path resourceFolderPath) {
    playerTexture = sf::Texture(resourceFolderPath / "player.png");
    player = Player(playerTexture);
    mapTexture = sf::Texture(resourceFolderPath / "maps.png");
    std::ifstream instream(resourceFolderPath / "maps.json");
    std::stringstream buffer;
    buffer << instream.rdbuf();
    nlohmann::json json = nlohmann::json::parse(buffer.str());
    for (auto& j : json["maps"]) {
        namedMaps[j["name"]] = Map(j, mapTexture);
    }
    currentMap = &namedMaps[json["startMap"]];
    player.setPosition(sf::Vector2f(json["startPos"]["x"], json["startPos"]["y"]));
}

void GameWindow::draw() {
    auto window = sf::RenderWindow(sf::VideoMode({800u, 800u}), "CMake SFML Project");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            player.moveUp();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            player.moveLeft();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            player.moveDown();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            player.moveRight();
        }
        auto result = currentMap->colide(player);
        if (result.getType() == ColisionResult::EXIT) {
            changeMap(result.getTarget());
        }
        else if (result.getType() == ColisionResult::TELEPORT) {
            Map* map = &namedMaps[result.getTarget()];
            map->arrive(currentMap->getExitDirection());
            currentMap = map;
        }
        window.clear();
        currentMap->draw(window);
        player.draw(window);
        window.display();
    }
}