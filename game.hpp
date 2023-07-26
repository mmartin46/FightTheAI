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
        pair<float, float> scroll;
        
    public:
        Game();
        void loadTextures();
        void loadWorld();
        void render();
        void animate();
        void collisionManager();
        void eventHandler(SDL_Window *window, SDL_Event &event, int &done);
        
        // Player

        inline void setPlayer(const Player &p) { player = p; }
        inline Player* getPlayer() { return &player; };

        inline void setScrollX(int s) { scroll.first = s; }
        inline int getScrollX() { return scroll.first; }

        inline void setScrollY(int s) { scroll.second = s; }
        inline int getScrollY() { return scroll.second; }
 
        // Renderer

        inline void setRenderer(SDL_Renderer *r) { renderer = r; }
        inline SDL_Renderer* getRenderer() { return renderer; }


        template <typename T>
        int mapCollision(T &plyr, Matrix<Entity> &blocks, int row, int col, int PLAYER_WIDTH, int PLAYER_HEIGHT);

        // Textures

        inline void setBlockTexture(SDL_Texture *t) { blockTexture =  t; }
        inline SDL_Texture* getBlockTexture() { return blockTexture; }

        // Time
        inline int getTime() { return time; }
        inline void setTime(int t) { time = t; }

        
};

template <typename T>
int Game::mapCollision(T &plyr, Matrix<Entity> &blocks, int row, int col, int PLAYER_WIDTH, int PLAYER_HEIGHT)
{
    int touched = 0;
    float pw = PLAYER_WIDTH, ph = PLAYER_HEIGHT;
    float px = plyr.get_x(), py = plyr.get_y();
    float bx = blocks.at(row).at(col).get_x(), by = blocks.at(row).at(col).get_y(), bw = blocks.at(row).at(col).get_w(), bh = blocks.at(row).at(col).get_h();

    if (px+pw/2 > bx && px+pw/2 < bx+bw)
    {
        // Head Bump
        if (py < by+bh && py>by && plyr.get_dy() < 0)
        {
            // correct y
            plyr.set_y(by+bh);
            py = by+bh;

            // bumped our head, stop any jump velocity
            plyr.set_dy(0);
            plyr.resetOnBlock();
            touched = 1;
        }
    }
    if (px+pw > bx && px<bx+bw)
    {
        // Head bump
        if (py+ph > by && py < by && plyr.get_dy() > 0)
        {
            // correct y
            plyr.set_y(by-ph);
            py = by-ph;

            //landed on this ledge, stop any jump velocity
            plyr.set_dy(0);
            plyr.setOnBlock();
            touched = 2;
        }
    }

    if (py+ph > by && py<by+bh)
    {
        // Rubbing against right edge
        if (px < bx+bw && px+pw > bx+bw && plyr.get_dx() < 0)
        {
            // correct x
            plyr.set_x(bx+bw);
            px = bx+bw;

            plyr.set_dx(0);
            touched = 3;
        }
        // Rubbing against left edge
        else if (px+pw > bx && px < bx && plyr.get_dx() > 0)
        {
            // correct x
            plyr.set_x(bx-pw);
            px = bx-pw;

            plyr.set_dx(0);
            touched = 4;
        }
    }
    return touched;
}

void Game::collisionManager()
{
    int row, col = 0;
    for (row = 0; row < 100; ++row)
    {
        for (col = 0; col < 100; ++col)
        {
            if (this->layer1.at(row).at(col) == world::BLOCK)
            {
                mapCollision(*getPlayer(), this->blocks, row, col, 20, 20);
            }
        }
    }
}

Game::Game()
{
    setTime(0);
    setScrollX(0);
    setScrollY(0);

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
            layer1.at(i).at(j) = world::map[i][j];
        }
    }

    for (int x = 0; x < 100; ++x)
    {
        for (int y = 0; y < 100; ++y)
        {
            // Intialize the map
            switch(layer1.at(x).at(y))
            {
                case world::BLOCK: {
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
    // Timer
    setTime(getTime() + 1);


    getPlayer()->set_x(getPlayer()->get_x() + getPlayer()->get_dx());
    getPlayer()->set_y(getPlayer()->get_y() + getPlayer()->get_dy());

    // Gravity
    getPlayer()->applyGravity();

    // Scrolling
    this->setScrollX(-getPlayer()->get_x() + SCREEN_WIDTH / 2);
    this->setScrollY(-getPlayer()->get_y() + SCREEN_HEIGHT / 2);

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
                case world::BLOCK : {
                    rect = { static_cast<int>(getScrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(getScrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
                    SDL_RenderCopy(this->getRenderer(), getBlockTexture(), NULL , &rect);
                } break;
            }
        }
    }

    rect = { static_cast<int>(getScrollX() + getPlayer()->get_x()), static_cast<int>(getScrollY() + getPlayer()->get_y()), getPlayer()->get_h(), getPlayer()->get_w() };
    SDL_RenderCopy(this->getRenderer(), getPlayer()->getTexture(getPlayer()->getFrame()), NULL, &rect);

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

        getPlayer()->setTexture(idx, SDL_CreateTextureFromSurface(this->getRenderer(), surface));
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
