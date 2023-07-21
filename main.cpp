// John 3:16
#include "utilities.cpp"
#include "entity.hpp"
#include "player.hpp"

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

/*
Objective 

Try to make a shooter similar
to the one at Children's Lighthouse

*/









class Game
{
    private:
        SDL_Renderer *renderer;
        std::shared_ptr<Entity> player;
    public:
        Game();
        void eventHandler(SDL_Window *window, SDL_Event &event, int &done);
        
        inline std::shared_ptr<Entity> getPlayer() { return player; };

        inline void set_renderer(SDL_Renderer *r) { renderer = r; }
        inline SDL_Renderer* get_renderer() { return renderer; }
};

Game::Game()
{
    player = std::shared_ptr<Player>(); 
}


void Game::eventHandler(SDL_Window *window, SDL_Event &event, int &done)
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
                done = 1;
            break;
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        done = 1;
                    break;
                }
            }
            break;
        }
    }
}

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
    game.set_renderer(renderer);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);


    int done = 0;

    SDL_Event event;
    while (!done)
    {
        game.eventHandler(window, event, done);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(game.get_renderer());
    return 0;
}