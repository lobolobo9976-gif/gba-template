
#include <gba.h>

int main()
{
    irqInit();
    irqEnable(IRQ_VBLANK);
    SetMode(MODE_3 | BG2_ENABLE);

    // Fondo de color oscuro
    for (int y = 0; y < 160; y++)
    {
        for (int x = 0; x < 240; x++)
        {
            MODE3_FB[y * 240 + x] =
                RGB5(3, 5, 12);
        }
    }

    int px = 120;
    int py = 80;

    while (1)
    {
        VBlankIntrWait();

        scanKeys();
        u16 keys = keysHeld();

        if ((keys & KEY_LEFT)  && px > 5)   px--;
        if ((keys & KEY_RIGHT) && px < 234) px++;
        if ((keys & KEY_UP)    && py > 5)   py--;
        if ((keys & KEY_DOWN)  && py < 154) py++;

        // Limpiar la zona donde estaba el personaje
        for (int y = py - 3; y <= py + 3; y++)
        {
            for (int x = px - 3; x <= px + 3; x++)
            {
                MODE3_FB[y * 240 + x] =
                    RGB5(3, 5, 12);
            }
        }

        // Dibujar un personaje provisional
        for (int y = py - 4; y <= py + 4; y++)
        {
            for (int x = px - 3; x <= px + 3; x++)
            {
                MODE3_FB[y * 240 + x] =
                    RGB5(10, 20, 31);
            }
        }
    }
}
