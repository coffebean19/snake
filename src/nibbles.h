#include "raylib.h"
typedef struct Nibble {
    int x;
    int y;
} Nibble;

extern Nibble* CreateNibble(int x, int y);
extern void DrawNibble(Nibble* nibble);
extern Rectangle DeriveNibbleRec(const Nibble* nibble);
void DestroyNibble(Nibble* nibble);