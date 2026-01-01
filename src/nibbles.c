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
    if (nibble == NULL) {
        return;
    }
    DrawRectangleRounded( (Rectangle) { 
        (float)nibble->x,
        (float)nibble->y,
        33,
        33
    },
      0.3f, 0, RED);
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