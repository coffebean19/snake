typedef enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
} direction;

typedef enum snake_block {
    HEAD,
    BODY,
    TAIL,
} snake_block;

typedef struct snake_block_t{
    short x;
    short y;
    snake_block block;
    struct snake_block_t * next;  
} snake_block_t;

typedef struct Snake {
    snake_block_t* head;
    snake_block_t* tail;
    snake_block_t* current;
} Snake;

extern snake_block_t* CreateSnakeBlock(short x, short y);
extern void DrawSnake(snake_block_t* head);
extern void FreeSnake(snake_block_t* head);
extern void GrowSnake(Snake* snake);
extern Snake* CreateSnake(short x, short y);