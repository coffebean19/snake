#include "raylib.h"
typedef enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef enum snake_block {
    HEAD,
    BODY,
    TAIL,
} snake_block;

typedef struct snake_block_t{
    int x;
    int y;
    snake_block block;
    Direction direction;
    struct snake_block_t * next;  
} snake_block_t;

typedef struct Snake {
    snake_block_t* head;
    snake_block_t* tail;
    snake_block_t* current;
} Snake;

// extern snake_block_t* CreateSnakeBlock(short x, short y,);
extern void DrawSnake(snake_block_t* head);
extern void FreeSnake(snake_block_t* head);
extern void GrowSnake(Snake* snake);
extern Snake* CreateSnake(short x, short y);
extern void MoveSnake(Snake* snake);
extern void ChangeDirection(Snake* snake, Direction dir);
extern Rectangle DeriveSnakeHeadRec(const Snake *snake);
extern Rectangle DeriveSnakeRec(snake_block_t* block);
extern bool SnakeEatSnake(Snake* snake);