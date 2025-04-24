#pragma once
#include "raylib.h"
#include "triangle.h"

class spaceship
{
public:
    spaceship(float x, float y, float w, float h);
    void render() const;
    void set_speed(float x, float y);
    void add_forward_thrust(float amount);
    void rotate(float angle);
    void move(float max_x, float max_y);

protected:
    void update_position(float max_x, float max_y);
    void rotate_triangle(float angle);
    [[nodiscard]] Vector2 get_centroid() const;
    triangle position_;
    Vector2 speed_;
    Vector2 forward_;
};
