// John 3:16
#include "game.hpp"


/*
Objective 

Try to make a shooter similar
to the one at Children's Lighthouse

*/

int main(int argc, char **argv)
{
    Game game;
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
    game.setRenderer(renderer);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
    SDL_RenderSetLogicalSize(game.getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);

    game.loadTextures();
    game.loadWorld();

    int done = 0;

    SDL_Event event;
    while (!done)
    {

        game.eventHandler(window, event, done);
        game.animate();
        game.render();
        game.collisionManager();

    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(game.getRenderer());
    return 0;
}