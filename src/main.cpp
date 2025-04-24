#include "raylib.h"
#include "spaceship.h"

constexpr int FONT_SIZE = 10;
constexpr int PADDING = 10;
constexpr float THRUST_STRENGTH = 5;
constexpr float TURN_RATE = 3;

static void draw_ui(const int score, int screen_width)
{
	DrawText("Asteroids", PADDING,PADDING,FONT_SIZE, WHITE);
	const char* score_text = TextFormat("Score: %d", score);
	const int text_measure = MeasureText(score_text, FONT_SIZE);
	DrawText(score_text, screen_width - text_measure - PADDING,PADDING,FONT_SIZE, WHITE);
}

int main ()
{
	constexpr int screen_width = 512;
	constexpr int screen_height = 512;
	constexpr float spaceship_width = 10.0;
	constexpr float spaceship_height = 12.0;
	int score = 0;
	
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(screen_width, screen_height, "Asteroids");

	spaceship ship(
		static_cast<float>(screen_width) / 2 - spaceship_width / 2,
		static_cast<float>(screen_height) / 2 -  spaceship_height / 2,
		spaceship_width,
		spaceship_height
		);

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		float delta = GetFrameTime();
		BeginDrawing();

		ClearBackground(BLACK);

		if (IsKeyDown(KEY_W))
		{
			ship.add_forward_thrust(-THRUST_STRENGTH * delta);
		}

		if (IsKeyDown(KEY_S))
		{
			ship.add_forward_thrust(THRUST_STRENGTH * delta);
		}

		if (IsKeyDown(KEY_D))
		{
			ship.rotate(TURN_RATE * delta);
		}

		if (IsKeyDown(KEY_A))
		{
			ship.rotate(-TURN_RATE * delta);
		}

		ship.move(static_cast<float>(screen_width), static_cast<float>(screen_height));
		ship.render();
		draw_ui(score, screen_width);
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
