#include "raylib.h"
#include "snake.h"
#include "resource_dir.h"	
#include "nibbles.h"
#include <stdlib.h>

Nibble* CreateNibble(int x, int y) {
    Nibble* new_nibble = (Nibble*)malloc(sizeof(Nibble));
    if (!new_nibble) { // check for if malloc fails
        return NULL;
    }

    new_nibble->x =x;
    new_nibble->y =y;
    return new_nibble;
}


void DrawNibble(Nibble* nibble) {
    // SearchAndSetResourceDir("resources");
    // Texture nibble_img = LoadTexture("food.png");
    // DrawTexture(nibble_img, nibble->x, nibble->y, WHITE);
    DrawRectangle(nibble->x, nibble->y, 33, 33, RED);
}

Rectangle DeriveNibbleRec(const Nibble *nibble) {
    return (Rectangle) {
        (float)(nibble-> x),
        (float)(nibble-> y),
        32.0f,
        32.0f
    };
}

void DestroyNibble(Nibble* nibble) {
    free(nibble);
}