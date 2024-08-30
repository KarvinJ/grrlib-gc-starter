#include <grrlib.h>
#include <stdlib.h>
#include <ogc/pad.h>
#include "BMfont3_png.h"
// #include "alien_1_png.h"
#include "test_jpg_jpg.h"

#define BLACK 0x000000FF
#define WHITE 0xFFFFFFFF
#define GREEN 0x008000FF
#define YELLOW 0xFFFF00FF

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SPEED = 10;

bool isGamePaused = false;

typedef struct
{
    float x;
    float y;
    float w;
    float h;
    unsigned int color;
} Rectangle;

Rectangle bounds = {0, 0, 64, 64, WHITE};

void update()
{
    const u32 padHeld = PAD_ButtonsHeld(0);

    if (padHeld & PAD_BUTTON_LEFT && bounds.x > 0)
    {
        bounds.x -= SPEED;
    }

    else if (padHeld & PAD_BUTTON_RIGHT && bounds.x < SCREEN_WIDTH - bounds.w)
    {
        bounds.x += SPEED;
    }

    else if (padHeld & PAD_BUTTON_UP && bounds.y > 0)
    {
        bounds.y -= SPEED;
    }

    else if (padHeld & PAD_BUTTON_DOWN && bounds.y < SCREEN_HEIGHT - bounds.h)
    {
        bounds.y += SPEED;
    }
}

int main(int argc, char **argv)
{
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();

    // loading images jpg
    // GRRLIB_texImg *tex_test_jpg = GRRLIB_LoadTexture(test_jpg_jpg);

    // loading fonts
    GRRLIB_texImg *tex_BMfont3 = GRRLIB_LoadTexture(BMfont3_png);

    // To indicate the font region to load.
    GRRLIB_InitTileSet(tex_BMfont3, 32, 32, 32);

    // Initialise the GameCube controllers
    PAD_Init();

    // Loop forever
    while (true)
    {
        PAD_ScanPads(); // Scan the GameCube controllers

        const u32 padDown = PAD_ButtonsDown(0);

        // If A was pressed on the first GameCube controller, break out of the loop
        if (padDown & PAD_BUTTON_A)
        {
            break;
        }

        if (padDown & PAD_BUTTON_START)
        {
            isGamePaused = !isGamePaused;
        }

        if (!isGamePaused)
        {
            update();
        }

        GRRLIB_FillScreen(BLACK);

        // ---------------------------------------------------------------------
        // Place your drawing code below
        // ---------------------------------------------------------------------

        // displaying text with the loaded fonts.
        if (isGamePaused)
        {
            GRRLIB_Printf(150, 20, tex_BMfont3, WHITE, 1, "GAME PAUSED");
        }

        // Draw jpg img
        //  GRRLIB_DrawImg(10, 50, tex_test_jpg, 0, 1, 1, WHITE);

        GRRLIB_Rectangle(bounds.x, bounds.y, bounds.w, bounds.h, bounds.color, 1);

        GRRLIB_Render(); // Render the frame buffer to the TV
    }

    GRRLIB_FreeTexture(tex_BMfont3); // Be a good boy, clear the memory allocated by GRRLIB

    GRRLIB_Exit();
    exit(0); // Use exit() to exit a program, do not use 'return' from main()
}
