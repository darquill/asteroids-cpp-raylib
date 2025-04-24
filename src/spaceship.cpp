#include "spaceship.h"

#include <cmath>
#include "raymath.h"

float constexpr MAX_SPEED = 8;

spaceship::spaceship(const float x, const float y, const float w, const float h)
{
    position_.p1.x = x;
    position_.p1.y = y;
    position_.p2.x = x - w / 2;
    position_.p2.y = y + h;
    position_.p3.x = x + w / 2;
    position_.p3.y = y + h;
    speed_.x = 0;
    speed_.y = 0;
    forward_.x = 0;
    forward_.y = 1;
}

void spaceship::render() const
{
    DrawTriangle(position_.p1, position_.p2, position_.p3, WHITE);
}

void spaceship::set_speed(float x, float y)
{
    speed_.x = x;
    speed_.y = y;
}

void spaceship::add_forward_thrust(float const amount)
{
    speed_ = Vector2ClampValue(Vector2Add(speed_, forward_ * amount), 0, MAX_SPEED);
}

void spaceship::rotate(float const angle)
{
    rotate_triangle(angle);
    forward_ = Vector2Rotate(forward_, angle);
}

void spaceship::move(float const max_x, float const max_y)
{
    update_position(max_x, max_y);
}

void spaceship::update_position(float const max_x, float const max_y)
{
    position_.p1 = Vector2Add(position_.p1, speed_);
    position_.p2 = Vector2Add(position_.p2, speed_);
    position_.p3 = Vector2Add(position_.p3, speed_);

    auto [cx, cy] = get_centroid();

    // Teleport to other side of screen if OOB on X
    if (cx > max_x)
    {
        position_.p1 = Vector2Subtract(position_.p1, {max_x, 0});
        position_.p2 = Vector2Subtract(position_.p2, {max_x, 0});
        position_.p3 = Vector2Subtract(position_.p3, {max_x, 0});
    } else if (cx < 0)
    {
        position_.p1 = Vector2Add(position_.p1, {max_x, 0});
        position_.p2 = Vector2Add(position_.p2, {max_x, 0});
        position_.p3 = Vector2Add(position_.p3, {max_x, 0});
    }

    // Teleport to other side of screen if OOB on Y
    if (cy > max_y)
    {
        position_.p1 = Vector2Subtract(position_.p1, {0, max_y});
        position_.p2 = Vector2Subtract(position_.p2, {0, max_y});
        position_.p3 = Vector2Subtract(position_.p3, {0, max_y});
    } else if (cy < 0)
    {
        position_.p1 = Vector2Add(position_.p1, {0, max_y});
        position_.p2 = Vector2Add(position_.p2, {0, max_y});
        position_.p3 = Vector2Add(position_.p3, {0, max_y});
    }
}

void spaceship::rotate_triangle(float angle)
{
    Vector2 const centroid = get_centroid();

    triangle const translated = {
        Vector2Subtract(position_.p1, centroid),
        Vector2Subtract(position_.p2, centroid),
        Vector2Subtract(position_.p3, centroid),
    };

    Vector2 const r1 = {
        translated.p1.x * std::cos(angle) - translated.p1.y * std::sin(angle),
        translated.p1.x * std::sin(angle) + translated.p1.y * std::cos(angle)
    };
    Vector2 const r2 = {
        translated.p2.x * std::cos(angle) - translated.p2.y * std::sin(angle),
        translated.p2.x * std::sin(angle) + translated.p2.y * std::cos(angle)
    };
    Vector2 const r3 = {
        translated.p3.x * std::cos(angle) - translated.p3.y * std::sin(angle),
        translated.p3.x * std::sin(angle) + translated.p3.y * std::cos(angle)
    };

    position_.p1 = Vector2Add(r1, centroid);
    position_.p2 = Vector2Add(r2, centroid);
    position_.p3 = Vector2Add(r3, centroid);
}

Vector2 spaceship::get_centroid() const
{
    Vector2 const centroid = {
        (position_.p1.x + position_.p2.x + position_.p3.x) / 3,
        (position_.p1.y + position_.p2.y + position_.p3.y) / 3
    };

    return centroid;
}

