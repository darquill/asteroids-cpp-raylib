#pragma once
#include <vector>
#include "asteroid.h"
#include "raylib.h"

class projectile
{
public:
    projectile(Vector2 forward, float x, float y);
    void render(bool debug_mode) const;
    void move(float delta);
    bool is_out_of_bounds(float max_x, float max_y) const;
    Vector2 get_position() const;
    std::vector<::asteroid>::const_iterator check_collision(const std::vector<asteroid>& asteroids) const;
protected:
    Vector2 position_;
    Vector2 speed_;
};
