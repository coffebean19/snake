/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "snake.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main ()
{
	Direction current_direction = UP; 
	SetTargetFPS(60);

	Snake* snake = CreateSnake(432, 232);
	GrowSnake(snake);
	GrowSnake(snake);
	GrowSnake(snake);
	GrowSnake(snake);
	snake->head->direction = RIGHT;

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
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
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
		MoveSnake(snake);

		DrawSnake(snake->head);



		sprintf(text_FPS, "%d", GetFPS());
		DrawText(text_FPS, 150, 200, 20, WHITE);
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
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
