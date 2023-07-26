#pragma once
#include "entity.hpp"

enum class status {
    DIDSHOOT = 0,
    DIDNTSHOOT 
};


class Shot : public Entity
{
    private:
        /* data */
        float x, y;
        int w, h;
        float dx, dy;
        int onBlock;
        bool landed;
        int animFrame;
        int frame;

        status shotStatus; 
        // Images
        std::vector<SDL_Texture*> textures;
    public:
        Shot();
        Shot(int x, int y, unsigned int size);
        status getDidShoot() { return shotStatus; }
        inline void resetDidShoot() { shotStatus = status::DIDNTSHOOT; }
        inline void setDidShoot() { shotStatus = status::DIDSHOOT; }
};


Shot::Shot()
{
    set_x(0);
    set_y(0);
    set_w(getImageDimensions("sprites\\shot\\shot.png").first);
    set_h(getImageDimensions("sprites\\shot\\shot.png").second);
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
