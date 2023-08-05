#include "game.hpp"

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

