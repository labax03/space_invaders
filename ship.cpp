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

void Ship::update(const float& dt)
{
    // Base Ship does nothing.
    // Player and Invader override this.
}

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
    // Horizontal movement
    move(dt * (direction ? 1.f : -1.f) * speed, 0.f);

    // Edge bounce
    if ((direction && getPosition().x > param::game_width - param::sprite_size / 2.f) ||
        (!direction && getPosition().x < param::sprite_size / 2.f)) {

        direction = !direction;
        speed += param::invader_acc;

        for (auto& s : gs::ships)
            s->move(0.f, 24.f);
    }

    // Random firing
    static float firetime = 0.f;
    firetime -= dt;

    if (firetime <= 0.f && rand() % 100 == 0) {
        Bullet::fire(getPosition(), true);
        firetime = 4.f + (rand() % 60);
    }
}
