#include "game_system.hpp"
#include "game_parameters.hpp"
#include "ship.hpp"
#include "bullet.hpp"
#include <iostream>

sf::Texture GameSystem::spritesheet;
std::vector<std::shared_ptr<Ship>> GameSystem::ships;

void GameSystem::init() {
    if (!spritesheet.loadFromFile("C:/users/user/space_invaders/resources/invaders_sheet.png")) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
    }

    // Add player first
    ships.push_back(std::make_shared<Player>());

    // Spawn invaders
    for (int r = 0; r < Parameters::rows; ++r) {
        for (int c = 0; c < Parameters::columns; ++c) {

            sf::IntRect rect(
                sf::Vector2i(0, r * Parameters::sprite_size),
                sf::Vector2i(Parameters::sprite_size, Parameters::sprite_size)
            );

            sf::Vector2f pos(
                50.f + c * (Parameters::sprite_size + 10),
                50.f + r * (Parameters::sprite_size + 10)
            );

            ships.push_back(std::make_shared<Invader>(rect, pos));
        }
    }
}

void GameSystem::update(const float &dt) {
    for (auto &s : ships)
        s->update(dt);

    Bullet::update(dt);
}

void GameSystem::render(sf::RenderWindow& window) {
    for (const auto& s : ships)
        window.draw(*s);

    Bullet::render(window);
}

void GameSystem::clean() {
    for (auto& s : ships)
        s.reset();
    ships.clear();
}
