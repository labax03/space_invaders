#include "bullet.hpp"
#include "game_system.hpp"
#include "game_parameters.hpp"

using param = Parameters;
using gs = GameSystem;

unsigned char Bullet::_bulletPointer = 0;
Bullet Bullet::_bullets[256];

Bullet::Bullet() {}

void Bullet::init() {
    for (int i = 0; i < 256; i++) {
        _bullets[i].setTexture(gs::spritesheet);
        _bullets[i].setOrigin(param::sprite_size / 2.f, param::sprite_size / 2.f);
        _bullets[i].setPosition(-100.f, -100.f);
    }
}

void Bullet::fire(const sf::Vector2f& pos, bool mode) {
    Bullet& b = _bullets[++_bulletPointer];

    b._mode = mode;

    if (mode)
        b.setTextureRect(sf::IntRect(160, 32, 32, 32)); // enemy bullet
    else
        b.setTextureRect(sf::IntRect(160, 0, 32, 32));  // player bullet

    b.setPosition(pos);
}

void Bullet::update(const float& dt) {
    for (int i = 0; i < 256; i++)
        _bullets[i]._update(dt);
}

void Bullet::render(sf::RenderWindow& window) {
    for (int i = 0; i < 256; i++)
        window.draw(_bullets[i]);
}

void Bullet::_update(const float& dt) {
    if (getPosition().y < -param::sprite_size ||
        getPosition().y > param::game_height + param::sprite_size)
        return;

    move(0.f, dt * param::bullet_speed * (_mode ? 1.f : -1.f));
}
