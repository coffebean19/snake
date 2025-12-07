typedef struct Nibble {
    short x;
    short y;
} Nibble;

extern Nibble* CreateNibble(short x, short y);
extern void DrawNibble(Nibble* nibble);