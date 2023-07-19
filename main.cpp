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


class Player {
    
};

class Movement {
    private:
        int x;
        int y;
        int dx;
        int dy;
    public:
        inline int get_x() { return x; }
        inline void set_x(int v) { x = v; }
        inline int get_y() { return y; }
        inline void set_y(int v) { y = v; }
        inline int get_dx() { return dx; }
        inline void set_dx(int v) { dx = v; }
        inline int get_dy() { return dy; }
        inline void set_dy(int v) { dy = v; }
};

class Game
{
    private:
        SDL_Renderer *renderer;
    public:
        inline void set_renderer(SDL_Renderer *r) { renderer = r; }
        inline SDL_Renderer* get_renderer() { return renderer; }
};

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
    mov.set_x(0);
    mov.set_y(0);

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
                            mov.set_y(mov.get_y() - 1);
                        }
                        break;
                        case SDLK_DOWN: {
                            mov.set_y(mov.get_y() + 1);
                        }
                        break;
                        case SDLK_LEFT: {
                            mov.set_x(mov.get_x() - 1);
                        }
                        break;
                        case SDLK_RIGHT: {
                            mov.set_y(mov.get_y() + 1);
                        }
                    }
                }
            }
        }
        std::cout << mov.get_x() << " " << mov.get_y() << std::endl;
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    return 0;
}