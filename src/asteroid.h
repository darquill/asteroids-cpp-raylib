#pragma once
#include <cstdint>
#include "raylib.h"

enum class asteroid_type : std::uint8_t {
    SMALL_ASTEROID = 0,
    MEDIUM_ASTEROID = 1,
    LARGE_ASTEROID = 2
};

class asteroid
{
public:
    asteroid(asteroid_type type, Vector2 center);
    void render(bool debug_mode);
    void move(float max_x, float max_y, float delta);
    Vector2 get_position() const;
    float radius;

protected:
    asteroid_type type_;
    Vector2 position_;
    Vector2 speed_;
};
