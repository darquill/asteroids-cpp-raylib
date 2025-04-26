#include <random>
#include "asteroid.h"
#include "raylib.h"
#include "raymath.h"

asteroid::asteroid(asteroid_type type, Vector2 center)
{
    type_ = type;
    
    switch (type)
    {
    case asteroid_type::SMALL_ASTEROID:
        radius = 5.0;
        break;
    case asteroid_type::MEDIUM_ASTEROID:
        radius = 15.0;
        break;
    case asteroid_type::LARGE_ASTEROID:
        radius = 25.0;
        break;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    float random_speed_x = (std::uniform_real_distribution<float>(1.0f, 50.0f))(gen);
    float random_speed_y = (std::uniform_real_distribution<float>(1.0f, 50.0f))(gen);

    position_ = center;
    speed_ = { random_speed_x, random_speed_y};
}

void asteroid::render(bool debug_mode)
{
    DrawCircleLines(position_.x, position_.y, radius, WHITE);
}

void asteroid::move(float max_x, float max_y, float delta)
{
    position_ = Vector2Add(position_, speed_ * delta);

    if (position_.x > max_x)
    {
        position_ = Vector2Subtract(position_, {max_x, 0});
    } else if (position_.x < 0)
    {
        position_ = Vector2Add(position_, {max_x, 0});
    }

    if (position_.y > max_y)
    {
        position_ = Vector2Subtract(position_, {0, max_y});
    } else if (position_.x < 0)
    {
        position_ = Vector2Add(position_, {0, max_y});
    }
}

Vector2 asteroid::get_position() const
{
    return position_;
}
