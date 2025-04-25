#include "asteroid.h"

#include "raylib.h"

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

    position = center;
}

void asteroid::render()
{
    DrawCircleLines(position.x, position.y, radius, WHITE);
}
