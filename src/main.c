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
#define NIBBLE_SPAWN_INTERVAL 2.0f

static Snake* snake;
static Direction current_direction = UP;
static Nibble *nibbles[MAX_NIBBLES];
static bool paused = false;
static Color grid_line_white = {255, 255, 255, 100};
static float nibbleSpawnTimer = 0.0f;

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
    if (IsKeyPressed(KEY_P)) {
      paused = !paused;
    }
  }
  return NULL;
}

void DrawGridLines() {
  float grid_line_pos = 0.0f;
  while (grid_line_pos < GetScreenHeight()) {
    DrawLineEx((Vector2){0.0f, grid_line_pos},
               (Vector2){(float)GetScreenWidth(), grid_line_pos}, 1.0f,
               grid_line_white);
    grid_line_pos += 32.0f;
  }

  grid_line_pos = 0.0f;
  while (grid_line_pos < GetScreenWidth()) {
    DrawLineEx((Vector2){grid_line_pos, 0},
               (Vector2){grid_line_pos, (float)GetScreenHeight()}, 1.0f,
               grid_line_white);
    grid_line_pos += 32.0f;
  }
}

bool EatNibble(Nibble *nibble) {
  if (!snake || !snake->head || !nibble) {
    return false;
  }

  return (
      CheckCollisionRecs(DeriveSnakeHeadRec(snake), DeriveNibbleRec(nibble)));
}

bool NibbleAndSnakeCollide(Rectangle nibble) {
  snake_block_t *current = snake->head;

  while (current != NULL) {
    for (int i = 0; i < MAX_NIBBLES; i++) {
      if (CheckCollisionRecs(DeriveSnakeRec(current),
                             nibble)) {
        return true;
      }
    }
    if (current->next) {
      current = current->next;
    } else {
      return false;
    }
  }
  return false;
}

void UpdateNibbleSpawning() {
  nibbleSpawnTimer += GetFrameTime();

  if (nibbleSpawnTimer < NIBBLE_SPAWN_INTERVAL) {
    return;
  }

  nibbleSpawnTimer = 0.0f;

  for (int i = 0; i < MAX_NIBBLES; i++) {
    if (nibbles[i] == NULL) {
      bool spawned = false;
      int x = 0;
      int y = 0;

      while (!spawned) {
        x = GetRandomValue(0, GetScreenWidth() - 32);
        y = GetRandomValue(0, GetScreenHeight() - 32);
        x = x - (x % 32);
        y = y - (y % 32);
        Rectangle new_nibble_col = (Rectangle) {
          (float)x,
          (float)y,
          32.0f,
          32.0f
        };

        if (!NibbleAndSnakeCollide(new_nibble_col)) {
          spawned = true;
        }
      }

      nibbles[i] = CreateNibble(x, y);
      break;
    }
  }
}

int main() {

  pthread_t input_thread;

  // Start input thread
  pthread_create(&input_thread, NULL, inputThread, NULL);
  SetTargetFPS(60);

  snake = CreateSnake(320, 320);
  GrowSnake(snake);
  GrowSnake(snake);
  GrowSnake(snake);
  snake->head->direction = RIGHT;

  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(1280, 800, "Hello Raylib");

  // Utility function from resource_dir.h to find the resources folder and set
  // it as the current working directory so we can load from it
  // SearchAndSetResourceDir("resources");
  // Texture snake_texture = LoadTexture("snake-block.png");

  char text_FPS[2];
  char delta_time[10];
  char nibbles_pos[50];
  // game loop
  while (!WindowShouldClose()) // run the loop until the user presses ESCAPE or
                               // presses the Close button on the window
  {

    // Texture snake_texture = LoadTexture("snake-block.png");
    sprintf(delta_time, "%.2f", GetFrameTime());
    sprintf(text_FPS, "%d", GetFPS());

    if (!paused) {
      UpdateNibbleSpawning();
      MoveSnake(snake);
      ChangeDirection(snake, current_direction);
    }

    for (int i = 0; i < MAX_NIBBLES; i++) {
      if (nibbles[i] != NULL && EatNibble(nibbles[i])) {
        DestroyNibble(nibbles[i]);
        nibbles[i] = NULL;
        printf("GrowSnake called\n");
        GrowSnake(snake);
        printf("GrowSnake finished\n");

        break;
      }
    }

    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(BLACK);

    DrawGridLines();

    // draw some text using the default font

    DrawSnake(snake->head);

    for (int i = 0; i < MAX_NIBBLES; i++) {
      if (nibbles[i] != NULL) {
        DrawNibble(nibbles[i]);
        DrawText(TextFormat("%d", i), nibbles[i]->x, nibbles[i]->y, 10, WHITE);
        sprintf(nibbles_pos, "Exists: true (%d, %d)", nibbles[i]->x,
                nibbles[i]->y);
        DrawText(nibbles_pos, 1000, 200 + i * 18, 20, WHITE);
      } else {
        DrawText("Exists: false", 1000, 200 + i * 18, 20, WHITE);
      }
    }

    DrawText("Snake game", 10, 10, 20, WHITE);
    DrawText(text_FPS, 150, 200, 20, WHITE);
    DrawText(delta_time, 150, 220, 20, WHITE);
    if (paused) {
      DrawText("PAUSED", GetScreenWidth() / 2 - 140, GetScreenHeight() / 2 - 80,
               120, WHITE);
    }
    // end the frame and get ready for the next one  (display frame, poll input,
    // etc...)
    EndDrawing();
  }

  // cleanup
  // unload our texture so it can be cleaned up
  // UnloadTexture(snake_texture);
  FreeSnake(snake->head);

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
