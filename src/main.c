/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit
https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h" // utility header for SearchAndSetResourceDir

#include "nibbles.h"
#include "snake.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NIBBLES 10

static Direction current_direction = UP;
static Nibble *nibbles[MAX_NIBBLES];
static bool paused = false;

void *inputThread(void *args) {
  // Direction current_direction = UP;
  while (1) {

    if (IsKeyDown(KEY_A)) {
      current_direction = LEFT;
    }
    if (IsKeyDown(KEY_S)) {
      current_direction = DOWN;
    }
    if (IsKeyDown(KEY_D)) {
      current_direction = RIGHT;
    }
    if (IsKeyDown(KEY_W)) {
      current_direction = UP;
    }
    if (IsKeyDown(KEY_P)) {
      paused = !paused;
    }
  }
  return NULL;
}

void *nibbleSpawnThread(void *args) {
  srand((unsigned int)time(NULL));

  int x = 0;
  int y = 0;
  while (1) {
    if (!paused) {
      x = rand() % 1280;
      y = rand() % 800;
	  x = x - (x % 32) - 1;
	  y = y - (y % 32) - 1;
      for (int i = 0; i < MAX_NIBBLES; i++) {
        if (nibbles[i] == NULL) {
          nibbles[i] = CreateNibble(x, y);
          break;
        }
      }
      WaitTime(2.0);
    }
  }
}

void DrawGridLines() {
  int grid_line_pos = 0;
    while (grid_line_pos < GetScreenHeight()) {
      DrawLine(0, grid_line_pos, GetScreenWidth(), grid_line_pos, WHITE);
      grid_line_pos += 32;
    }

    grid_line_pos = 0;
    while (grid_line_pos < GetScreenWidth()) {
      DrawLine(grid_line_pos, 0, grid_line_pos, GetScreenHeight(), WHITE);
      grid_line_pos += 32;
    }
}

int main() {

  pthread_t input_thread;
  pthread_t nibbles_thread;

  // Start input thread
  pthread_create(&input_thread, NULL, inputThread, NULL);
  pthread_create(&nibbles_thread, NULL, nibbleSpawnThread, NULL);

  SetTargetFPS(10);

  Snake *snake = CreateSnake(320, 320);
  GrowSnake(snake);
  GrowSnake(snake);
  snake->head->direction = RIGHT;


  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(1280, 800, "Hello Raylib");

  // Utility function from resource_dir.h to find the resources folder and set
  // it as the current working directory so we can load from it
  SearchAndSetResourceDir("resources");
  Texture snake_texture = LoadTexture("snake-block.png");

  char text_FPS[2];
  char delta_time[10];
  char nibbles_pos[50];
  // game loop
  while (!WindowShouldClose()) // run the loop until the user presses ESCAPE or
                               // presses the Close button on the window
  {
    sprintf(delta_time, "%.2f", GetFrameTime());
    sprintf(text_FPS, "%d", GetFPS());

    if (!paused) {
      MoveSnake(snake);
      ChangeDirection(snake, current_direction);
    }

    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(BLACK);

    DrawGridLines();

    // draw some text using the default font
    DrawText("Snake game", 10, 10, 20, WHITE);

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
        sprintf(nibbles_pos, "Exists: true (%d, %d)", nibbles[i]->x,
                nibbles[i]->y);
        DrawText(nibbles_pos, 1000, 200 + i * 18, 20, WHITE);
      } else {
        DrawText("Exists: false", 1000, 200 + i * 18, 20, WHITE);
      }
    }

    DrawText(text_FPS, 150, 200, 20, WHITE);
    DrawText(delta_time, 150, 220, 20, WHITE);
    // end the frame and get ready for the next one  (display frame, poll input,
    // etc...)
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
