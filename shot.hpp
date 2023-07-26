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
        std::vector<SDL_Texture*> textures;
    public:
        Shot();
        Shot(int x, int y, unsigned int size);
        Shot(Entity *e);
        Shot(Entity *e, unsigned int size);
};

Shot::Shot()
{
    set_x(0);
    set_y(0);
    set_dx(0);
    set_dy(0);
    textures = std::vector<SDL_Texture*>(1);
}

Shot::Shot(int x, int y, unsigned int size)
{
    set_x(x);
    set_y(y);
    set_dx(0);
    set_dy(0);
    textures = std::vector<SDL_Texture*>(size);
}

Shot::Shot(Entity *e)
{
    set_x(e->get_x());
    set_y(e->get_y());
    set_dx(e->get_dx());
    set_dy(e->get_dy());
    textures = std::vector<SDL_Texture*>(1);
}

Shot::Shot(Entity *e, unsigned int size)
{
    set_x(e->get_x());
    set_y(e->get_y());
    set_dx(e->get_dx());
    set_dy(e->get_dy());
    textures = std::vector<SDL_Texture*>(size);
}