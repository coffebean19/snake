/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "snake.h"
#include "nibbles.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main ()
{
	Direction current_direction = UP; 
	SetTargetFPS(10);

	Snake* snake = CreateSnake(432, 232);
	GrowSnake(snake);
	GrowSnake(snake);
	GrowSnake(snake);
	GrowSnake(snake);
	snake->head->direction = RIGHT;

	Nibble *nibble1 = CreateNibble(500,500);
	Nibble *nibble2 = CreateNibble(600,600);
	Nibble *nibble3 = CreateNibble(700,700);
	Nibble *nibble4 = CreateNibble(800,650);

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	Texture snake_texture = LoadTexture("snake-block.png");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	char text_FPS[2];
	char delta_time[10];
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		sprintf(delta_time, "%.2f", GetFrameTime()); 
		sprintf(text_FPS, "%d", GetFPS());
		MoveSnake(snake);
		if (IsKeyDown('A') || IsKeyDown('a')) {
			current_direction = LEFT;
		}
		if (IsKeyDown('S') || IsKeyDown('s')) {
			current_direction = DOWN;
		}
		if (IsKeyDown('D') || IsKeyDown('d')) {
			current_direction = RIGHT;
		}
		if (IsKeyDown('W') || IsKeyDown('w')) {
			current_direction = UP;
		}

		ChangeDirection(snake, current_direction);

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawText("Hello Raylib", 200,200,20,WHITE);

		// draw our texture to the screen
		if (IsKeyDown('A') || IsKeyDown('a')) {
			DrawText("a", 400, 150, 20, WHITE);
		}
		if (IsKeyDown('S') || IsKeyDown('s')) {
			DrawText("s", 400, 150, 20, WHITE);
		}
		if (IsKeyDown('D') || IsKeyDown('d')) {
			DrawText("d", 400, 150, 20, WHITE);
		}
		if (IsKeyDown('W') || IsKeyDown('w')) {
			DrawText("w", 400, 150, 20, WHITE);
		}

		DrawSnake(snake->head);
		DrawNibble(nibble1);
		DrawNibble(nibble2);
		DrawNibble(nibble3);
		DrawNibble(nibble4);

		DrawText(text_FPS, 150, 200, 20, WHITE);
		DrawText(delta_time, 150, 220, 20, WHITE);
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
		// WaitTime(0.2);
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);
	UnloadTexture(snake_texture);
	FreeSnake(snake->head);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
