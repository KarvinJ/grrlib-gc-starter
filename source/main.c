/*===========================================
        GRRLIB (GX Version)
        - Template Code -

        Minimum Code To Use GRRLIB
============================================*/
#include <grrlib.h>

#include <stdlib.h>
#include <ogc/pad.h>
#include "BMfont2_png.h"
// #include "alien_1_png.h"
#include "test_jpg_jpg.h"

#define GRRLIB_BLACK 0x000000FF
#define GRRLIB_WHITE 0xFFFFFFFF

typedef struct
{
    float x;
    float y;
    float w;
    float h;
} Rectangle;

int main(int argc, char **argv)
{
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();

    Rectangle bounds = {0, 0, 64, 64};

    const int SCREEN_WIDHT = 640;
    const int SCREEN_HEIGHT = 480;
    const int SPEED = 10;

    //loading fonts. 
    GRRLIB_texImg *tex_BMfont2 = GRRLIB_LoadTexture(BMfont2_png);
    // To indicate the font region to load.
    GRRLIB_InitTileSet(tex_BMfont2, 16, 16, 32);

    // Initialise the GameCube controllers
    PAD_Init();

    // Loop forever
    while (1)
    {
        PAD_ScanPads(); // Scan the GameCube controllers

        const u32 paddown = PAD_ButtonsDown(0);
        const u32 padheld = PAD_ButtonsHeld(0);

        GRRLIB_FillScreen(GRRLIB_BLACK);

            // displaying text with the loaded fonts.
        GRRLIB_Printf(300, 25, tex_BMfont2, GRRLIB_WHITE, 1, "DEMO");

        // If [START/PAUSE] was pressed on the first GameCube controller, break out of the loop
        if (paddown & PAD_BUTTON_START)
        {
            break;
        }
        if (padheld & PAD_BUTTON_LEFT && bounds.x > 0)
        {
            bounds.x -= SPEED;
        }
        if (padheld & PAD_BUTTON_RIGHT && bounds.x < SCREEN_WIDHT - bounds.w)
        {
            bounds.x += SPEED;
        }
        if (padheld & PAD_BUTTON_UP && bounds.y > 0)
        {
            bounds.y -= SPEED;
        }
        if (padheld & PAD_BUTTON_DOWN && bounds.y < SCREEN_HEIGHT - bounds.h)
        {
            bounds.y += SPEED;
        }

        // ---------------------------------------------------------------------
        // Place your drawing code here
        // ---------------------------------------------------------------------

        GRRLIB_Rectangle(bounds.x, bounds.y, bounds.w, bounds.h, GRRLIB_WHITE, 1);

        GRRLIB_Render(); // Render the frame buffer to the TV
    }

    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB

    exit(0); // Use exit() to exit a program, do not use 'return' from main()
}
