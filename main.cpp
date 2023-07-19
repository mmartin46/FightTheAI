#include <iostream>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_mixer.h>
#include <SDL2\SDL_ttf.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

/*
Objective 

Try to make a shooter similar
to the one at Children's Lighthouse

*/
int main(int argc, char **argv)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    window = SDL_CreateWindow(
        "Shooter",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);


    int done = 0;

    while (!done)
    {

    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    return 0;
}