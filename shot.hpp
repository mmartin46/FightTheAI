#pragma once
#include "entity.hpp"

class Shot : public Entity
{
    private:
        /* data */
        float x, y;
        int w, h;
        float dx, dy;
        int frame;
        std::vector<SDL_Texture*> sprites;
    public:
};