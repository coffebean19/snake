#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "snake.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir



snake_block_t* CreateSnakeBlock(short x, short y) {
    snake_block_t * new_block = (snake_block_t*)malloc(sizeof(snake_block_t));
    if (new_block == NULL) {
        printf("Failed to create new block.\n");
        exit(1);
    }
    new_block->x=x;
    new_block->y=y;
    return new_block;
}

Snake* CreateSnake(short x, short y) {
    Snake* egg = (Snake*)malloc(sizeof(Snake)); // unborn snake
    snake_block_t* snakeling = CreateSnakeBlock(x,y); // snake is born
    egg->head = egg->tail = egg->current = snakeling;
    return egg;
}

void GrowSnake(Snake* snake) {
    snake_block_t* growth = CreateSnakeBlock(snake->tail->x, snake->tail->y);
    snake->tail->next = growth;
    snake->tail = growth;
}

void FreeSnake(snake_block_t* head) {
    free(head);
}

void DrawSnake(snake_block_t* head) {
    SearchAndSetResourceDir("resources");
	Texture snake = LoadTexture("snake-block.png");

    snake_block_t* block = head;
    while (block != NULL) {
        DrawTexture(snake, block->x, block->y, WHITE);
        block = block->next;
    }
}