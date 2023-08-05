#include "game.hpp"


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

