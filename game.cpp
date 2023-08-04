#include "game.hpp"
#include "animation.cpp"
#include "render.cpp"

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
                mapCollision(*getPlayer(), *this->getBlocks(), row, col, 20, 30);
                mapCollision(*getShot(), *this->getBlocks(), row, col, 5, 5);
                mapCollision(*getEnemy(), *this->getBlocks(), row, col, 20, 30);
            }
        }
    }
}

Game::Game()
{
    setTime(0);
    setScrollX(0);
    setScrollY(0);

    setScreenHeight(SCREEN_HEIGHT);
    setScreenWidth(SCREEN_WIDTH);

    getPlayer()->set_x(200);
    getPlayer()->set_y(200);
    getPlayer()->set_dx(0);
    getPlayer()->set_dy(0);

    getEnemy()->set_x(200);
    getEnemy()->set_y(200);
    getEnemy()->set_dx(0);
    getEnemy()->set_dy(0);

    getBackground()->set_x(0);
    getBackground()->set_y(0);
    getBackground()->set_w(420);
    getBackground()->set_h(240);

    getSmoke()->setFrame(4);

    attackedPlayer = getPlayer();
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

// Make the shot position match a specific player
void Game::matchShotPosition(Player *player)
{
    getShot()->set_x(player->get_x() + 10);
    getShot()->set_y(player->get_y() + 5);
}




void Game::loadTextures()
{
    using std::string;

    SDL_Surface *surface = NULL;
    string filePath;
    int idx;


    // Font
    setFont(TTF_OpenFont("sprites\\fonts\\font.ttf", 14));
    if (getFont() == nullptr)
    {
        std::cout << "loader font(): Can't find font";
        SDL_Quit();
        exit(1);
    }

    // Player files
    for (idx = 0; idx < 19; ++idx)
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

    // Enemy
    for (idx = 0; idx < 19; ++idx)
    {
        filePath = "sprites\\enemy\\player" + std::to_string(idx) + ".png";
        surface = IMG_Load(filePath.c_str());
        if (surface == NULL)
        {
            std::cout << "loadTextures enemy(): No texture for " + filePath << std::endl;
            SDL_Quit();
            exit(1);
        }
        if (idx == 0)
        {
            getEnemy()->set_w(getImageDimensions(filePath.c_str()).first);
            getEnemy()->set_h(getImageDimensions(filePath.c_str()).second);
        }
        getEnemy()->setTexture(idx, SDL_CreateTextureFromSurface(this->getRenderer(), surface));
        SDL_FreeSurface(surface);
    }

    // Background
    filePath = "sprites\\background\\bg.jpg";
    surface = IMG_Load(filePath.c_str());
    if (surface == NULL)
    {
        std::cout << "loadTextures background(): No texture for " + filePath << std::endl;
        SDL_Quit();
        exit(1);        
    }
    getBackground()->setTexture(0, SDL_CreateTextureFromSurface(this->getRenderer(), surface));
    SDL_FreeSurface(surface);


    for (idx = 1; idx <= 5; ++idx)
    {
        filePath = "sprites\\attacked\\smoke" + std::to_string(idx) + ".png";
        surface = IMG_Load(filePath.c_str());
        if (surface == NULL)
        {
            std::cout << "loadTextures smoke(): No texture for " + filePath << std::endl;
            SDL_Quit();
            exit(1);
        }
        getSmoke()->setTexture((idx-1), SDL_CreateTextureFromSurface(this->getRenderer(), surface));
        SDL_FreeSurface(surface);
   }

    // Blocks
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

    filePath = "sprites\\shot\\shot.png";
    surface = IMG_Load(filePath.c_str());
    if (surface == NULL)
    {
        std::cout << "loadTextures shot(): No texture for " + filePath << std::endl;
        SDL_Quit();
        exit(1);
    }
    setShotTexture(SDL_CreateTextureFromSurface(this->getRenderer(), surface));
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

    // Attacks
    if (state[SDL_SCANCODE_SPACE])
    {
        shotMovement();
    }

    // Camera
    if (state[SDL_SCANCODE_W])
    {
        zoomOut();
    }
    else if (state[SDL_SCANCODE_S])
    {
        zoomIn();
    }



    if (state[SDL_SCANCODE_UP])
    {
        getPlayer()->setMovingUp();
        getPlayer()->applyJump();
    }
    if (state[SDL_SCANCODE_LEFT])
    {
        getPlayer()->setMovingLeft();
        getPlayer()->leftMovement(3);
    }
    else if (state[SDL_SCANCODE_RIGHT])
    {
        getPlayer()->setMovingRight();
        getPlayer()->rightMovement(3);
    }
    else
    {
        getPlayer()->resetDoAttack_0();
        getPlayer()->resetDoAttack_1();
        if (getPlayer()->get_dy() != 0)
        {
            getPlayer()->resetKeys();
        }
        getPlayer()->downMovement();
    }

    enemyPlayerCollision(state);
}

void Game::initGameStatsBar()
{
   char str[200] = "";
   sprintf(str, "Player 1: %d%     Player 2: %d%        Time: %u             ", (int)(getPlayer()->getDamage() * 10), (int)(getEnemy()->getDamage() * 10), (this->getTime()));

   SDL_Color white = { 255, 255, 255, 255 };
   SDL_Surface *tmp = TTF_RenderText_Blended(this->getFont(), str, white);
   gameStatsBar.set_w(tmp->w);
   gameStatsBar.set_h(tmp->h);
   gameStatsBar.setTexture(0, SDL_CreateTextureFromSurface(this->getRenderer(), tmp));
   SDL_FreeSurface(tmp);
}


void Game::enemyPlayerCollision(const Uint8* state)
{
    if (state[SDL_SCANCODE_Q])
    {
        getPlayer()->setDoAttack_0();
        if (collide2d(playerEnemyCollision))
        {
            attackedPlayer = getEnemy();
            allowSmokeAnimation();


            getEnemy()->incDamage();
            getEnemy()->setFunctionalityOff();
            if (getPlayer()->getFacingLeft())
            {
                getEnemy()->set_dx(-3 * getEnemy()->getDamage());
                getEnemy()->set_dy(-2 * getEnemy()->getDamage());
            }
            else
            {
                getEnemy()->set_dx(3 * getEnemy()->getDamage());
                getEnemy()->set_dy(-2 * getEnemy()->getDamage());                
            }
        }
    }    
    
    if (state[SDL_SCANCODE_DOWN])
    {
        getPlayer()->setMovingDown();
        if (collide2d(playerEnemyCollision))
        {
            attackedPlayer = getEnemy();
            allowSmokeAnimation();

            getEnemy()->incDamage();
            getEnemy()->setFunctionalityOff();
            if (getPlayer()->getFacingLeft())
            {
                getEnemy()->set_dx(-2 * getEnemy()->getDamage());
                getEnemy()->set_dy(-3 * getEnemy()->getDamage());
            }
            else
            {
                getEnemy()->set_dx(2 * getEnemy()->getDamage());
                getEnemy()->set_dy(-3 * getEnemy()->getDamage());                
            }
        }    

    }

    if (((getTime() % 50) == 0) && !getEnemy()->getFunctionality())
    {
        getEnemy()->setFunctionalityOn();
    }
}


void Game::shotMovement()
{
    switch (getShot()->getDidShoot())
    {
        case status::DIDSHOOT : {
            getShot()->resetDidShoot();
            break;
        }
        case status::DIDNTSHOOT : {
            getShot()->setDidShoot();
            break;
        }
    }
}