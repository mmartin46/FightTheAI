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
        void events();
        
        inline std::shared_ptr<Entity> getPlayer() { return player; };

        inline void set_renderer(SDL_Renderer *r) { renderer = r; }
        inline SDL_Renderer* get_renderer() { return renderer; }
};

Game::Game()
{
    player = std::shared_ptr<Player>(); 
}

void Game::events()
{

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

    Player mov;

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
                        case SDLK_ESCAPE: {
                            done = 1;
                        }
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
                            mov.set_x(mov.get_x() + 1);
                        }
                        break;
                    }
                }
            }
        }
        std::cout << mov.get_x() << " " << mov.get_y() << std::endl;
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(game.get_renderer());
    return 0;
}