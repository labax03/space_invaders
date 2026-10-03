#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Ship;
class Player;

class GameSystem {
public:
    static sf::Texture spritesheet;
    static std::vector<std::shared_ptr<Ship>> ships;
    static std::shared_ptr<Player> player;

    static void init();
    static void update(const float& dt);
    static void render(sf::RenderWindow& window);
    static void clean();
};
