#include "ship.hpp"
#include "game_system.hpp"
#include "game_parameters.hpp"
#include "bullet.hpp"

using param = Parameters;
using gs = GameSystem;

// ---------------- SHIP ----------------

Ship::Ship() {}

Ship::Ship(const Ship& s) : _sprite(s._sprite) {}

Ship::Ship(sf::IntRect ir) : Sprite() {
    _sprite = ir;
    setTexture(gs::spritesheet);
    setTextureRect(_sprite);
}

Ship::~Ship() = default;

void Ship::update(const float& dt) {}

bool Ship::is_exploded() const {
    return _exploded;
}

void Ship::explode() {
    setTextureRect(sf::IntRect(sf::Vector2i(128, 32), sf::Vector2i(32, 32)));
    _exploded = true;
}

// ---------------- INVADER ----------------

bool Invader::direction = true;
float Invader::speed = param::invader_speed;

Invader::Invader() : Ship() {}

Invader::Invader(const Invader& inv) : Ship(inv) {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
    setOrigin(param::sprite_size / 2.f, param::sprite_size / 2.f);
    setPosition(pos);
}

void Invader::move_down() {
    move(0.f, 24.f);
}

void Invader::update(const float& dt) {
    Ship::update(dt);

    move(dt * (direction ? 1.f : -1.f) * speed, 0.f);

    if ((direction && getPosition().x > param::game_width - param::sprite_size / 2.f) ||
        (!direction && getPosition().x < param::sprite_size / 2.f)) {

        direction = !direction;
        speed += param::invader_acc;

        for (auto& s : gs::ships)
            s->move(0.f, 24.f);
    }

    static float firetime = 0.f;
    firetime -= dt;

    if (firetime <= 0.f && rand() % 100 == 0) {
        Bullet::fire(getPosition(), true);
        firetime = 4.f + (rand() % 60);
    }
}

// ---------------- PLAYER ----------------

Player::Player() :
    Ship(sf::IntRect(sf::Vector2i(param::sprite_size * 5, param::sprite_size),
        sf::Vector2i(param::sprite_size, param::sprite_size))) {

    setOrigin(param::sprite_size / 2.f, param::sprite_size / 2.f);
    setPosition(param::game_width / 2.f, param::game_height - param::sprite_size);
}

void Player::update(const float& dt) {
    Ship::update(dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        move(-200.f * dt, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        move(200.f * dt, 0.f);

    static float firetime = 0.f;
    firetime -= dt;

    if (firetime <= 0.f && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        Bullet::fire(getPosition(), false);
        firetime = 0.5f;
    }
}
