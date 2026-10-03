#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
public:
    Ship();
    Ship(const Ship& s);
    Ship(sf::IntRect ir);
    virtual ~Ship() = 0;

    virtual void update(const float& dt);

    bool is_exploded() const;
    virtual void explode();

protected:
    sf::IntRect _sprite;
    bool _exploded = false;
};

// ---------------- INVADER ----------------

class Invader : public Ship {
public:
    static bool direction;
    static float speed;

    Invader();
    Invader(const Invader& inv);
    Invader(sf::IntRect ir, sf::Vector2f pos);

    void update(const float& dt) override;
    void move_down();
};

// ---------------- PLAYER ----------------

class Player : public Ship {
public:
    Player();
    void update(const float& dt) override;
};
