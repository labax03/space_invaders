#include "game_system.hpp"
#include "game_parameters.hpp"
#include "ship.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include <iostream>

sf::Texture GameSystem::spritesheet;
std::vector<std::shared_ptr<Ship>> GameSystem::ships;
std::shared_ptr<Player> GameSystem::player;

void GameSystem::init() {
    if (!spritesheet.loadFromFile("C:/users/user/space_invaders/resources/invaders_sheet.png")) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
    }

    // Create player
    player = std::make_shared<Player>();

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

void GameSystem::update(const float& dt) {
    // Update player first
    player->update(dt);

    // Update invaders
    for (auto& s : ships)
        s->update(dt);

    // Update bullets
    Bullet::update(dt);
}

void GameSystem::render(sf::RenderWindow& window) {
    // Draw player
    window.draw(*player);

    // Draw invaders
    for (const auto& s : ships)
        window.draw(*s);

    // Draw bullets
    Bullet::render(window);
}

void GameSystem::clean() {
    for (auto& s : ships)
        s.reset();
    ships.clear();

    player.reset();
}
