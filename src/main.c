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
#include <pthread.h>
#include <time.h>

#define MAX_NIBBLES 10

static Direction current_direction = UP;
static Nibble* nibbles[MAX_NIBBLES];

void* inputThread(void* args) {
	// Direction current_direction = UP; 
	while (1) {

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
	}
	return NULL;
}

void* nibbleSpawnThread(void* args) {
	srand((unsigned int)time(NULL));

	int x = 0;
	int y = 0;
	while (1) {
		x = rand() % 1200;
		y = rand() % 800;
		for (int i = 0; i < MAX_NIBBLES; i++) {
			if (nibbles[i] == NULL) {
				nibbles[i] = CreateNibble(x, y);
				break;
			}
		}
		WaitTime(2.0);
	}
}

int main ()
{

	pthread_t input_thread;
	pthread_t nibbles_thread;

	// Start input thread
	pthread_create(&input_thread, NULL, inputThread, NULL);
	pthread_create(&nibbles_thread, NULL, nibbleSpawnThread, NULL);

	SetTargetFPS(60);

	Snake* snake = CreateSnake(320, 320);
	GrowSnake(snake);
	GrowSnake(snake);
	GrowSnake(snake);
	GrowSnake(snake);
	snake->head->direction = RIGHT;


	Nibble *nibble1 = CreateNibble(342,512);
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

	char text_FPS[2];
	char delta_time[10];
	char nibbles_pos[50];
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		sprintf(delta_time, "%.2f", GetFrameTime()); 
		sprintf(text_FPS, "%d", GetFPS());
		MoveSnake(snake);
		ChangeDirection(snake, current_direction);

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawText("Snake game", 10,10,20,WHITE);

		if (IsKeyDown('A') || IsKeyDown('a')) {
			DrawText("a", 200, 10, 20, WHITE);
		}
		if (IsKeyDown('S') || IsKeyDown('s')) {
			DrawText("s", 200, 10, 20, WHITE);
		}
		if (IsKeyDown('D') || IsKeyDown('d')) {
			DrawText("d", 200, 10, 20, WHITE);
		}
		if (IsKeyDown('W') || IsKeyDown('w')) {
			DrawText("w", 200, 10, 20, WHITE);
		}

		DrawSnake(snake->head);

		for (int i = 0; i < MAX_NIBBLES; i++) {
			if (nibbles[i] != NULL) {
				DrawNibble(nibbles[i]);
				sprintf(nibbles_pos, "Exists: true (%d, %d)", nibbles[i]->x, nibbles[i]->y);
				DrawText(nibbles_pos, 1000, 200 + i * 18, 20, WHITE);
			} else {
				DrawText("Exists: false", 1000, 200 + i * 18, 20, WHITE);
			}
		}

		DrawText(text_FPS, 150, 200, 20, WHITE);
		DrawText(delta_time, 150, 220, 20, WHITE);
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
		WaitTime(0.1);
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(snake_texture);
	FreeSnake(snake->head);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
