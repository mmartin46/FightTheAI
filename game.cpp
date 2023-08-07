#include "game.hpp"

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
    disallowSmokeAnimation();

    layer1 = Matrix<int>(100, vector<int>(100));
    blocks = Matrix<Entity>(100, vector<Entity>(100));
}


// Make the shot position match a specific player
void Game::matchShotPosition(Player *player)
{
    getShot()->set_x(player->get_x() + 10);
    getShot()->set_y(player->get_y() + 5);
}



void Game::smokeAnimation()
{
    if (getSmokeAnimationState() == true)
    {
        if ((time % 10) < 10)
        {
            if ((time % 10) < 3.5)
            {
                getSmoke()->setFrame(0);
            }
            else if ((time % 10) >= 3.5 && (time % 20) < 5)
            {
                getSmoke()->setFrame(1);
            }
            else if ((time % 10) >= 5 && (time % 20) < 7.5)
            {
                getSmoke()->setFrame(2);
            }
            else if ((time % 10) >= 7.5 && (time % 10) < 10)
            {
                getSmoke()->setFrame(3);
            }
            else
            {
                disallowSmokeAnimation();
                getSmoke()->setFrame(4);
            }
        }
    }
}

void Game::animate()
{
    initGameStatsBar();
    // Timer
    setTime(getTime() + 1);

    // Set Enemy's Target
    getEnemy()->setupTarget(*getPlayer());

    // Player Movement
    getPlayer()->set_x(getPlayer()->get_x() + getPlayer()->get_dx());
    getPlayer()->set_y(getPlayer()->get_y() + getPlayer()->get_dy());

    getEnemy()->set_x(getEnemy()->get_x() + getEnemy()->get_dx());
    getEnemy()->set_y(getEnemy()->get_y() + getEnemy()->get_dy());

    //Shot Positioning
    if (getShot()->getDidShoot() == status::DIDNTSHOOT)
    {
        matchShotPosition(getPlayer());
    }
    else
    {
        getShot()->set_x(getShot()->get_x() + 1);
        getShot()->set_dx(getShot()->get_dx() + 0.5);
    }


    getPlayer()->animation(getTime());

    // Enemy Attacks
    getEnemy()->movement();
    
    
    if (getEnemy()->usePunchAttack(*playerEnemyCollision, getPlayer()))
    {
        attackedPlayer = getPlayer();
        allowSmokeAnimation();
        smokeAnimation();
    }
    if (getEnemy()->useSpinAttack(*playerEnemyCollision, getPlayer()))
    {
        attackedPlayer = getPlayer();
        allowSmokeAnimation();
        smokeAnimation();
    }

    getEnemy()->animation(getTime());



    getShot()->applyGravity();

    // Gravity
    getPlayer()->applyGravity();
    getEnemy()->applyGravity();

    // Scrolling
    this->setScrollX(-getPlayer()->get_x() + getScreenWidth() / 2);
    this->setScrollY(-getPlayer()->get_y() + getScreenHeight() / 2);

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
                    BLOCKS(x, y).set_y((x*BLOCK_WIDTH));
                    BLOCKS(x, y).set_x((y*BLOCK_HEIGHT));
                    BLOCKS(x, y).set_w(BLOCK_WIDTH);
                    BLOCKS(x, y).set_h(BLOCK_HEIGHT);
                }
                break;
            }
        }
    }
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

    // Movables
    playerTextureLoading(idx, 19, surface, getPlayer());
    playerTextureLoading(idx, 19, surface, getEnemy());


    // Object Texture Setters
    vector<entitysize_pair_<Entity*, int> > objects = {
        {(getSmoke()), 4},
        {(getBackground()), 1}
    };

    vector<pair<string, string> > messageMap = {
        {"sprites\\attacked\\smoke", "setObjectTextures smoke(): No texture for "},
        {"sprites\\background\\bg.jpg", "setObjectTextures background(): No texture for "}
    };

    // Iterate through the objects and set their textures.
    vector<entitysize_pair_<Entity*, int> >::pointer oPtr, oEnd = objects.data() + objects.size();
    typename vector<pair<string, string> >::pointer mPtr, mEnd = messageMap.data() + messageMap.size();
    for (oPtr = objects.data(), mPtr = messageMap.data(); oPtr < oEnd; ++oPtr, ++mPtr)
    {
        setObjectTextures(oPtr->first, oPtr->second, filePath, surface, *mPtr);
    }

    // Game Texture Setters
    vector<void (Game::*)(SDL_Texture *)> constantTextures = {
        setBlockTexture,
        setShotTexture
    };

    messageMap = {
        {"sprites\\platforms\\block.png", "constantTextures block(): No texture for "},
        {"sprites\\shot\\shot.png", "constantTextures shot(): No texture for "}
    };
    setConstantTextures(constantTextures, messageMap, surface, filePath);
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


/* 
Detects a collision between a player and a specific block,
and how the player is to be placed after the collision
*/
template <typename T>
int Game::mapCollision(T &plyr, Matrix<Entity> &blocks, int row, int col, int player_width, int player_height)
{
    int touched = 0;
    float pw = player_width, ph = player_height;
    float px = plyr.get_x(), py = plyr.get_y();
    float bx = BLOCKS(row, col).get_x(), by = BLOCKS(row, col).get_y(), bw = BLOCKS(row, col).get_w(), bh = BLOCKS(row, col).get_h();

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

/*
Manages all the collisions within
the map.
*/
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



/*
\param constantTextures vector of game texture setters
\param messageMap vector of string pairs
\param surface pointer to a surface
\param filePath to change by reference
*/
void Game::setConstantTextures(vector<void (Game::*)(SDL_Texture*)> &constantTextures, 
                            vector<pair<std::string, std::string> > &messageMap,
                            SDL_Surface *surface,
                            std::string &filePath)
{
    using std::string;

    typename vector<pair<string, string> >::pointer mPtr, mEnd = messageMap.data() + messageMap.size();
    typename vector<void (Game::*)(SDL_Texture *)>::pointer setTPtr, setTEnd = constantTextures.data() + constantTextures.size();

    for (mPtr = messageMap.data(), setTPtr = constantTextures.data(); mPtr < mEnd; ++mPtr, ++setTPtr)
    {

        filePath = mPtr->first;
        surface = IMG_Load(filePath.c_str());
        if (surface == NULL)
        {
            std::cout << mPtr->second + filePath << std::endl;
            SDL_Quit();
            exit(1);
        }
        (*this.**setTPtr)(SDL_CreateTextureFromSurface(this->getRenderer(), surface));
        SDL_FreeSurface(surface);
    }
}

/*
\param obj shared pointer to an object 
\param size # of textures
\param filePath to change by reference
\param surface pointer to a surface
\param image path and the error message
*/
void Game::setObjectTextures(Entity *obj, int size, 
                            std::string &filePath, SDL_Surface *surface,
                            pair<string, string> &messagePair)
{
    using std::to_string;

    /*
    By default the type of file for the image
    is a .png. If the type is of .jpg, change the
    file type.
    */
    string fileType = ".png";
    if (fileType.find(".jpg") != std::string::npos)
    {
        fileType = ".jpg";
    }

    /*
    If there is a number within the string, cut off the file type.
    */
    if (std::any_of(messagePair.first.begin(), messagePair.first.end(), ::isdigit))
    {
        messagePair.first = messagePair.first.substr(0, messagePair.first.find(".", 0));
    }

    int idx = 0;
    for (; idx < size; ++idx)
    {
        /*
        If there is only one texture, just keep the string as is.
        */
        if (size == 1)
        {
            filePath = messagePair.first;
        }
        else
        {
            filePath = messagePair.first + to_string(idx) + fileType;
        }
        surface = IMG_Load(filePath.c_str());
        if (surface == NULL)
        {
            std::cout << messagePair.second + filePath << std::endl;
            SDL_Quit();
            exit(1);
        }
        obj->setTexture(idx, SDL_CreateTextureFromSurface(this->getRenderer(), surface));
        SDL_FreeSurface(surface);
   }
}

/*
\param idx index to start on
\param size # of textures
\param surface pointer to the SDL_Surface
\param entity player to edit
*/
void Game::playerTextureLoading(int idx, int size, SDL_Surface *surface, Player *entity)
{
    string filePath;
    string filePathStart;

    // Checking the type of the object
    if (typeid(*entity) == typeid(Player))
    {
        filePathStart = "sprites\\player\\player";
    }
    else if (typeid(*entity) == typeid(Enemy))
    {
        filePathStart = "sprites\\enemy\\player";
    }
    else
    {
        std::cout << "loader playerTextureLoading(): object type not found";
        SDL_Quit();
        exit(1);
    }

    // Set the textures.
    for (idx = 0; idx < size; ++idx)
    {
        filePath = filePathStart + std::to_string(idx) + ".png";
        surface = IMG_Load(filePath.c_str());
        if (surface == NULL)
        {
            std::cout << "loadTextures player(): No texture for " + filePath << std::endl;
            SDL_Quit();
            exit(1);
        }
        if (idx == 0)
        {
            entity->set_w(getImageDimensions(filePath.c_str()).first);
            entity->set_h(getImageDimensions(filePath.c_str()).second);
        }
        entity->operator()(idx, SDL_CreateTextureFromSurface(this->getRenderer(), surface));
        SDL_FreeSurface(surface);
    }
}



void Game::render()
{
    SDL_SetRenderDrawColor(this->getRenderer(), 120, 120, 120, 255);
    SDL_RenderClear(this->getRenderer());
    SDL_Rect rect;

    // Background
    rect = { SCROLL((*getBackground()), (this->getScrollX() / 200), get_x()), SCROLL((*getBackground()), (this->getScrollY() / 20), get_y()), getBackground()->get_w(), getBackground()->get_h() };
    SDL_RenderCopy(this->getRenderer(), getBackground()->getTexture(0), NULL, &rect);


    int x, y;
    for (x = 0; x < MAP_WIDTH; ++x)
    {
        for (y = 0; y < MAP_HEIGHT; ++y)
        {
            switch(layer1.at(x).at(y))
            {
                case world::BLOCK : {
                    rect = { SCROLL(BLOCKS(x, y), getScrollX(), get_x()), SCROLL(BLOCKS(x, y), getScrollY(), get_y()), BLOCKS(x, y).get_w(), BLOCKS(x, y).get_h() };
                    SDL_RenderCopy(this->getRenderer(), getBlockTexture(), NULL , &rect);
                } break;
            }
        }
    }

    // Shot
    rect = { SCROLL((*getShot()), getScrollX(), get_x()), SCROLL((*getShot()), getScrollY(), get_y()), getShot()->get_h(), getShot()->get_w() };
    SDL_RenderCopy(this->getRenderer(), getShotTexture(), NULL, &rect);

    // Player
    rect = { SCROLL((*getPlayer()), getScrollX(), get_x()), SCROLL((*getPlayer()), getScrollY(), get_y()), getPlayer()->get_h(), getPlayer()->get_w() };
    SDL_RenderCopyEx(this->getRenderer(), GETFRAME(player), NULL, &rect, 0, NULL, ISFACINGLEFT(getPlayer()));

    // Enemy
    rect = { SCROLL((*getEnemy()), getScrollX(), get_x()), SCROLL((*getEnemy()), getScrollY(), get_y()), getEnemy()->get_h(), getEnemy()->get_w() };
    SDL_RenderCopyEx(this->getRenderer(), GETFRAME(enemy), NULL, &rect, 0, NULL, ISFACINGLEFT(getEnemy()));

    renderGameStatsBar(rect);
    makeSmokeRect(rect, attackedPlayer);


    playerEnemyCollision->x1 = player.get_x();
    playerEnemyCollision->y1 = player.get_y();
    playerEnemyCollision->wt1 = player.get_w();
    playerEnemyCollision->ht1 = player.get_h(); 

    playerEnemyCollision->x2 = enemy.get_x();
    playerEnemyCollision->y2 = enemy.get_y();
    playerEnemyCollision->wt2 = enemy.get_w();
    playerEnemyCollision->ht2 = enemy.get_h(); 


    SDL_RenderPresent(this->getRenderer());
}


template <typename T>
void Game::makeSmokeRect(SDL_Rect rect, T *plyr) 
{
    rect = { SCROLL((*plyr), getScrollX(), get_x()), SCROLL((*plyr), getScrollY(), get_y()), plyr->get_h(), plyr->get_w() };
    SDL_RenderCopyEx(this->getRenderer(), getSmoke()->getTexture(getSmoke()->getFrame()), NULL, &rect, 0, NULL, ISFACINGLEFT(getPlayer()));
}


void Game::renderGameStatsBar(SDL_Rect &rect)
{
    rect = { 0, 0, gameStatsBar.get_w(), gameStatsBar.get_h() };
    SDL_RenderCopy(this->getRenderer(), gameStatsBar.getTexture(0), NULL, &rect);
}

