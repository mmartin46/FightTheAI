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
        Player player;
    public:
        Game();
        void loadTextures();
        void render();
        void eventHandler(SDL_Window *window, SDL_Event &event, int &done);
        
        inline void setPlayer(const Player &p) { player = p; }
        inline Player* getPlayer() { return &player; };

        inline void setRenderer(SDL_Renderer *r) { renderer = r; }
        inline SDL_Renderer* getRenderer() { return renderer; }
};

Game::Game()
{
    getPlayer()->set_x(0);
    getPlayer()->set_y(0);
    getPlayer()->set_w(20);
    getPlayer()->set_h(20);
}

void Game::render()
{
    SDL_SetRenderDrawColor(this->getRenderer(), 120, 120, 120, 255);
    SDL_RenderClear(this->getRenderer());


    SDL_Rect rect;

    rect = { getPlayer()->get_x(), getPlayer()->get_y(), getPlayer()->get_h(), getPlayer()->get_w() };
    SDL_RenderCopy(this->getRenderer(), getPlayer()->getPlayerTexture(getPlayer()->getFrame()), NULL, &rect);

    SDL_RenderPresent(this->getRenderer());
}

void Game::loadTextures()
{
    using std::string;

    SDL_Surface *surface = NULL;
    string filePath;
    int idx;

    for (idx = 0; idx < 1; ++idx)
    {
        filePath = "sprites\\player\\player" + std::to_string(idx) + ".png";
        surface = IMG_Load(filePath.c_str());
        if (surface == NULL)
        {
            std::cout << "loadTextures player(): No texture for " + filePath;
            SDL_Quit();
            exit(1);
        }
        getPlayer()->setPlayerTexture(idx, SDL_CreateTextureFromSurface(this->getRenderer(), surface));
        SDL_FreeSurface(surface);
    }
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

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_LEFT])
        {
            getPlayer()->set_x(getPlayer()->get_x() - 1);
        }
        else if (state[SDL_SCANCODE_RIGHT])
        {
            getPlayer()->set_x(getPlayer()->get_x() + 1);
        }

        
        std::cout << getPlayer()->get_x() << std::endl;
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
    game.setRenderer(renderer);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
    SDL_RenderSetLogicalSize(game.getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);

    game.loadTextures();

    int done = 0;

    SDL_Event event;
    while (!done)
    {
        game.eventHandler(window, event, done);
        game.render();
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(game.getRenderer());
    return 0;
}