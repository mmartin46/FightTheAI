#include "entity.hpp"


Entity::Entity()
{
    this->set_x(0);
    this->set_y(0);
    textures = std::vector<SDL_Texture*>(10);
    this->setFrame(0);    
}

Entity::Entity(float x, float y, unsigned int size)
{
    this->set_x(x);
    this->set_y(y);
    textures = std::vector<SDL_Texture*>(size);
    this->setFrame(0);
}


void Entity::setTexture(int idx, SDL_Texture *texture)
{
    // If the index out of range.
    if (idx >= textures.size() || idx < 0)
    {
        std::cout << "setTexture(): Invalid Index\n";
        SDL_Quit();
        exit(1);
    }
    // Set the texture
    textures.at(idx) = texture;
}
