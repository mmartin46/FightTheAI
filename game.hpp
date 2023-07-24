#pragma once
#include "entity.hpp"
#include "player.hpp"
#include "map.cpp"

#define BLOCK_WIDTH 20
#define BLOCK_HEIGHT 20

class Game
{
    private:
        int time;
        SDL_Renderer *renderer;
        Player player;

        // Game Layers
        Matrix<int> layer1; 

        // Game Objects
        Matrix<Entity> blocks;

        // Game Textures
        SDL_Texture *blockTexture;

        // Scrolling
        pair<int, int> scroll;
        
    public:
        Game();
        void loadTextures();
        void loadWorld();
        void render();
        void animate();
        void eventHandler(SDL_Window *window, SDL_Event &event, int &done);
        
        // Player

        inline void setPlayer(const Player &p) { player = p; }
        inline Player* getPlayer() { return &player; };

        // Renderer

        inline void setRenderer(SDL_Renderer *r) { renderer = r; }
        inline SDL_Renderer* getRenderer() { return renderer; }


        // Textures

        inline void setBlockTexture(SDL_Texture *t) { blockTexture =  t; }
        inline SDL_Texture* getBlockTexture() { return blockTexture; }

        // Time

        inline int getTime() { return time; }
        inline void setTime(int t) { time = t; }

        
};

Game::Game()
{
    setTime(0);
    getPlayer()->set_x(200);
    getPlayer()->set_y(200);
    getPlayer()->set_dx(0);
    getPlayer()->set_dy(0);
    layer1 = Matrix<int>(100, vector<int>(100));
    blocks = Matrix<Entity>(100, vector<Entity>(100));
}

void Game::loadWorld()
{
    for (int i = 0; i < layer1.size(); ++i)
    {
        for (int j = 0; j < layer1.at(i).size(); ++j)
        {
            layer1.at(i).at(j) = map[i][j];
        }
    }

    for (int x = 0; x < 100; ++x)
    {
        for (int y = 0; y < 100; ++y)
        {
            // Intialize the map
            switch(layer1.at(x).at(y))
            {
                case 1: {
                    blocks.at(x).at(y).set_y((x*BLOCK_WIDTH));
                    blocks.at(x).at(y).set_x((y*BLOCK_HEIGHT));
                    blocks.at(x).at(y).set_w(BLOCK_WIDTH);
                    blocks.at(x).at(y).set_h(BLOCK_HEIGHT);
                }
                break;
            }
        }
    }
}


void Game::animate()
{
    setTime(getTime() + 1);

    getPlayer()->set_x(getPlayer()->get_x() + getPlayer()->get_dx());
    getPlayer()->set_y(getPlayer()->get_y() + getPlayer()->get_dy());

    // Temporary Gravity
    if (getPlayer()->get_y() < (WINDOW_HEIGHT - 20))
    {
        getPlayer()->applyGravity();
    }
    else
    {
        getPlayer()->set_dy(0);
        getPlayer()->setOnBlock();
    }

    std::cout << getPlayer()->get_dy() << std::endl;
}

void Game::render()
{
    SDL_SetRenderDrawColor(this->getRenderer(), 120, 120, 120, 255);
    SDL_RenderClear(this->getRenderer());




    SDL_Rect rect;

    int x, y;
    for (x = 0; x < 100; ++x)
    {
        for (y = 0; y < 100; ++y)
        {
            switch(layer1.at(x).at(y))
            {
                case 1 : {
                    rect = { blocks.at(x).at(y).get_x(), blocks.at(x).at(y).get_y(), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
                    SDL_RenderCopy(this->getRenderer(), getBlockTexture(), NULL , &rect);
                } break;
            }
        }
    }

    rect = { static_cast<int>(getPlayer()->get_x()), static_cast<int>(getPlayer()->get_y()), getPlayer()->get_h(), getPlayer()->get_w() };
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
            std::cout << "loadTextures player(): No texture for " + filePath << std::endl;
            SDL_Quit();
            exit(1);
        }
        if (idx == 0)
        {
            getPlayer()->set_w(getImageDimensions(filePath.c_str()).first);
            getPlayer()->set_h(getImageDimensions(filePath.c_str()).second);
        }

        getPlayer()->setPlayerTexture(idx, SDL_CreateTextureFromSurface(this->getRenderer(), surface));
        SDL_FreeSurface(surface);
    }


    filePath = "sprites\\platforms\\block.png";
    surface = IMG_Load(filePath.c_str());
    if (surface == NULL)
    {
        std::cout << "loadTextures block(): No texture for " + filePath << std::endl;
        SDL_Quit();
        exit(1);
    }
    setBlockTexture(SDL_CreateTextureFromSurface(this->getRenderer(), surface));
    SDL_FreeSurface(surface);

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
                    case SDLK_UP:
                        if (getPlayer()->getOnBlock())
                        {
                            getPlayer()->set_dy(static_cast<float>(PLAYERJUMPHEIGHT));
                            getPlayer()->resetOnBlock();
                        }
                }
            }
            break;
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP])
    {
        getPlayer()->applyJump();
    }
    if (state[SDL_SCANCODE_LEFT])
    {
        getPlayer()->leftMovement(3);
    }
    else if (state[SDL_SCANCODE_RIGHT])
    {
        getPlayer()->rightMovement(3);
    }
    else
    {
        getPlayer()->downMovement();
    }
}
