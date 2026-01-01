#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "snake.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "raylib.h"



snake_block_t* CreateSnakeBlock(short x, short y, Direction direction) {
    snake_block_t * new_block = (snake_block_t*)malloc(sizeof(snake_block_t));
    if (new_block == NULL) {
        printf("Failed to create new block.\n");
        exit(1);
    }
    new_block->x=x;
    new_block->y=y;
    new_block->direction=direction;

    return new_block;
}

Snake* CreateSnake(short x, short y) {
    Snake* egg = (Snake*)malloc(sizeof(Snake)); // unborn snake
    snake_block_t* snakeling = CreateSnakeBlock(x,y,UP); // snake is born
    egg->head = egg->tail = egg->current = snakeling; // It only has one block at creation, thus everything is set the same
    return egg;
}

void GrowSnake(Snake* snake) {
    snake_block_t* growth = CreateSnakeBlock(snake->tail->x, snake->tail->y+32,snake->tail->direction);
    snake->tail->next = growth;
    snake->tail = growth;
}

void FreeSnake(snake_block_t* head) {
    snake_block_t* current = head;
    snake_block_t* next;

    while (current != NULL) {
        next = current -> next;
        free(current);
        current = next;
    }
}

void DrawSnake(snake_block_t* head) {
    // SearchAndSetResourceDir("resources");
	// Texture snake = LoadTexture("snake-block.png");

    snake_block_t* block = head;
    while (block != NULL) {
        // DrawTexture(snake, block->x, block->y, WHITE);
        DrawRectangle(block->x, block->y, 32, 32, WHITE);
        block = block->next;
    }
}

void MoveSnake(Snake* snake) {
    int speed = 32;
    snake_block_t* body_piece = snake->head;
    Direction cur_dir = body_piece->direction;
    Direction prev_dir = body_piece -> direction;
    while (body_piece != NULL) {
        switch (body_piece->direction) {
            case UP:
                body_piece->y -= speed;
                break;            
            case DOWN:
                body_piece->y += speed;
                break;        
            case LEFT:
                body_piece->x -= speed;
                break;        
            case RIGHT:
                body_piece->x += speed;
                break;        
        }
        cur_dir = body_piece->direction;
        body_piece->direction = prev_dir;
        prev_dir = cur_dir;
        body_piece = body_piece->next;
    }
}

void MoveToHead(Snake* snake) {
    snake->current = snake->head;
}

void ChangeDirection(Snake* snake, Direction dir) {
    if ((snake->head->direction == UP && dir == DOWN) 
            || (snake->head->direction == DOWN && dir == UP) 
            || (snake->head->direction == RIGHT && dir == LEFT)
            || (snake->head->direction == LEFT && dir == RIGHT)) {
        return;
    }
    if (snake->head->direction != dir) {
        snake->head->direction = dir;
    }
}

Rectangle DeriveSnakeHeadRec(const Snake *snake) {
    return (Rectangle) {
        (float)(snake->head->x),
        (float)(snake->head->y),
        32.0f,
        32.0f
    };
}