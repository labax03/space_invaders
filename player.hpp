#pragma once
#include "ship.hpp"

class Player : public Ship {
public:
    Player();
    void update(const float& dt) override;
};
