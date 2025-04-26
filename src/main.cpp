#include <random>
#include <vector>

#include "asteroid.h"
#include "projectile.h"
#include "raylib.h"
#include "spaceship.h"

class projectile;
constexpr int FONT_SIZE = 10;
constexpr int PADDING = 10;
constexpr float THRUST_STRENGTH = 5;
constexpr float TURN_RATE = 3;

static void draw_ui(const int score, int screen_width, bool game_over)
{
	DrawText("Asteroids", PADDING,PADDING, FONT_SIZE, WHITE);
	const char* score_text = TextFormat("Score: %d", score);
	const int text_measure = MeasureText(score_text, FONT_SIZE);
	DrawText(score_text, screen_width - text_measure - PADDING,PADDING,FONT_SIZE, WHITE);

	if (game_over)
	{
		const int gameover_text_measure = MeasureText("Game Over", FONT_SIZE);
		DrawText("Game Over", screen_width / 2 - gameover_text_measure / 2,PADDING, FONT_SIZE, RED);
	}
}

int main ()
{
	static constexpr int screen_width = 512;
	static constexpr int screen_height = 512;
	constexpr float spaceship_width = 10.0;
	constexpr float spaceship_height = 12.0;
	int score = 0;
	bool game_over = false;
	bool initialized = false;
	bool debug_mode = false;
	constexpr float screen_center_x = static_cast<float>(screen_width) / 2;
	constexpr float screen_center_y = static_cast<float>(screen_height) / 2;
	int number_of_asteroids = 1;
	float rate_of_fire_timer = 0;
	std::vector<asteroid> asteroids;
	std::vector<projectile> projectiles;

	spaceship ship(spaceship_width, spaceship_height);
	
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(screen_width, screen_height, "Asteroids");

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		// Level initialization
		if (!initialized)
		{
			ship.reposition(screen_center_x, screen_center_y);
			
			std::random_device rd;
			std::mt19937 gen(rd());

			asteroids.clear();
			asteroids.reserve(number_of_asteroids);

			for (int i = 0; i < number_of_asteroids; ++i)
			{
				float random_x, random_y;

				// Prevent asteroids from spawning in the center of the screen where the ship is
				while (true)
				{
					random_x = (std::uniform_real_distribution<float>(0.0f, screen_width))(gen);
					random_y = (std::uniform_real_distribution<float>(0.0f, screen_height))(gen);

					if (constexpr float avoid_zone = 100.0f; random_x < screen_center_x - avoid_zone
					|| random_x > screen_center_x + avoid_zone
					|| random_y < screen_center_y - avoid_zone
					|| random_y > screen_center_y + avoid_zone)
					{
						break;
					}
				}
		
				asteroids.emplace_back(asteroid_type::LARGE_ASTEROID, Vector2{random_x, random_y });
			}

			initialized = true;
			number_of_asteroids++; // TODO remove when adding logic for winning levels
		}
		
		// Game logic
		float delta = GetFrameTime();
		rate_of_fire_timer += delta;
		BeginDrawing();

		ClearBackground(BLACK);

		if (IsKeyPressed(KEY_R))
		{
			initialized = false;
			game_over = false;
		}

		if (IsKeyPressed(KEY_Z))
		{
			debug_mode = !debug_mode;
		}

		if (initialized && !game_over)
		{
			if (IsKeyDown(KEY_W))
			{
				ship.add_forward_thrust(THRUST_STRENGTH * delta);
			}

			if (IsKeyDown(KEY_S))
			{
				ship.add_forward_thrust(-THRUST_STRENGTH * delta);
			}

			if (IsKeyDown(KEY_D))
			{
				ship.rotate(TURN_RATE * delta);
			}

			if (IsKeyDown(KEY_A))
			{
				ship.rotate(-TURN_RATE * delta);
			}

			if (IsKeyDown(KEY_SPACE) && rate_of_fire_timer > 0.5f)
			{
				auto [x, y] = ship.get_position();
				projectile p(ship.get_forward(), x, y);

				projectiles.emplace_back(p);
				rate_of_fire_timer = 0;
			}
			
			ship.move(static_cast<float>(screen_width), static_cast<float>(screen_height));
			ship.render(debug_mode);

			for (auto& asteroid : asteroids)
			{
				asteroid.move(static_cast<float>(screen_width), static_cast<float>(screen_height), delta);
				asteroid.render(debug_mode);
			}

			for (auto projectile = projectiles.begin(); projectile != projectiles.end();)
			{
				projectile->render(debug_mode);
				projectile->move(delta);

				auto asteroid = projectile->check_collision(asteroids);
				if (asteroid != asteroids.end())
				{
					asteroids.erase(asteroid);
					projectile = projectiles.erase(projectile);
				} else
				{
					++projectile;
				}
			}

			projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](const projectile& p)
			{
				return p.is_out_of_bounds(screen_width, screen_height);
			}), projectiles.end());

			if (ship.check_collision(asteroids))
			{
				game_over = true;
				number_of_asteroids = 1;
			}
		}
		
		draw_ui(score, screen_width, game_over);
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
