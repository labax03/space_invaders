#include "player.hpp"
#include "bullet.hpp"
#include "game_parameters.hpp"
#include <SFML/Window/Keyboard.hpp>

using param = Parameters;

Player::Player() :
    Ship(sf::IntRect(sf::Vector2i(param::sprite_size * 5, param::sprite_size),
        sf::Vector2i(param::sprite_size, param::sprite_size))) {

    setOrigin(param::sprite_size / 2.f, param::sprite_size / 2.f);
    setPosition(param::game_width / 2.f, param::game_height - param::sprite_size);
}

void Player::update(const float& dt)
{
    // movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        move(-param::player_speed * dt, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        move(param::player_speed * dt, 0.f);

    // firing bullets
    static float fireCooldown = 0.f;
    fireCooldown -= dt;

    if (fireCooldown <= 0.f && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        Bullet::fire(getPosition(), false);   // false = player bullet
        fireCooldown = 0.25f;
    }
}
