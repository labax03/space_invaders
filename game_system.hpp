#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Ship;

struct GameSystem {
    static sf::Texture spritesheet;
    static std::vector<std::shared_ptr<Ship>> ships;

    static void init();
    static void update(const float& dt);
    static void render(sf::RenderWindow& window);
    static void clean();
};
