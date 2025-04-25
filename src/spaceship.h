#pragma once
#include <vector>

#include "asteroid.h"
#include "raylib.h"
#include "triangle.h"

class spaceship
{
public:
    spaceship(float w, float h);
    void reposition(float x, float y);
    void render(bool debug_mode) const;
    void set_speed(float x, float y);
    void add_forward_thrust(float amount);
    void rotate(float angle);
    void move(float max_x, float max_y);
    bool check_collision(const std::vector<asteroid>&) const;
    Rectangle bounding_box;

protected:
    void update_position(float max_x, float max_y);
    void rotate_triangle(float angle);
    void set_bounding_box(float w, float h);
    [[nodiscard]] Vector2 get_centroid() const;
    Vector2 dimensions_;
    triangle position_;
    Vector2 speed_;
    Vector2 forward_;
};
