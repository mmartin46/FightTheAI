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

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
} Movement;

void eventHandler(int &done)
{

}


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

    Movement mov;
    mov.x = 0;
    mov.y = 0;

    SDL_Event event;
    while (!done)
    {

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_WINDOWEVENT_CLOSE:
                {
                    if (window)
                    {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        done = 1;
                    }
                }
                break;
                case SDL_QUIT:
                {
                    done = 1;
                }
                break;
                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            done = 1;
                        break;
                        case SDLK_UP: {
                            mov.y += 1;
                        }
                        break;
                        case SDLK_DOWN: {
                            mov.y -= 1;
                        }
                        break;
                        case SDLK_LEFT: {
                            mov.x -= 1;
                        }
                        break;
                        case SDLK_RIGHT: {
                            mov.x += 1;
                        }
                    }
                }
            }
        }
        std::cout << mov.x << " " << mov.y << std::endl;
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    return 0;
}