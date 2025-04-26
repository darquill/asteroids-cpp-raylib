#include "projectile.h"
#include <algorithm>

#include "raymath.h"

projectile::projectile(Vector2 forward, float x, float y)
{
    speed_ = Vector2Scale(forward, 500.0f);
    position_ = {x, y};
}

void projectile::render(bool debug_mode) const
{
    DrawCircle(position_.x, position_.y, 1, WHITE);
}

void projectile::move(float delta)
{
    position_ = Vector2Add(position_, speed_ * delta);
}

bool projectile::is_out_of_bounds(float max_x, float max_y) const
{
    return position_.x > max_x || position_.y > max_y || position_.x < 0 || position_.y < 0;
}

Vector2 projectile::get_position() const
{
    return position_;
}

std::vector<::asteroid>::const_iterator projectile::check_collision(const std::vector<asteroid>& asteroids) const
{
    Vector2 pos = position_;

    return std::find_if(asteroids.begin(), asteroids.end(), [pos](const asteroid& asteroid)
    {
        return CheckCollisionCircles(asteroid.get_position(), asteroid.radius, pos, 1);
    });
}
