#include "game.hpp"


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