#pragma once

struct Parameters {
    static constexpr int game_width = 800;
    static constexpr int game_height = 600;
    static constexpr int sprite_size = 32;

    static constexpr int rows = 5;
    static constexpr int columns = 11;

    static constexpr float invader_speed = 20.f;
    static constexpr float invader_acc = 2.f;

    static constexpr float bullet_speed = 200.f;   
};
