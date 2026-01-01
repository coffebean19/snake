#include "raylib.h"
typedef struct Nibble {
    int x;
    int y;
} Nibble;

extern Nibble* CreateNibble(short x, short y);
extern void DrawNibble(Nibble* nibble);
extern Rectangle DeriveNibbleRec(const Nibble *nibble);