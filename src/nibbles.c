#include "snake.h"
#include "resource_dir.h"	
#include "nibbles.h"
#include <stdlib.h>

Nibble* CreateNibble(short x, short y) {
    Nibble* new_nibble = (Nibble*)malloc(sizeof(Nibble));
    new_nibble->x =x;
    new_nibble->y =y;
    return new_nibble;
}

void NibbleEaten() {

}

void DrawNibble(Nibble* nibble) {
    // SearchAndSetResourceDir("resources");
    // Texture nibble_img = LoadTexture("food.png");
    // DrawTexture(nibble_img, nibble->x, nibble->y, WHITE);
    DrawRectangle(nibble->x, nibble->y, 32, 32, RED);
}