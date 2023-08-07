#include "shot.hpp"

Shot::Shot()
{
    resetTimer();
    resetDidShoot();
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
    resetDidShoot();
    set_x(x);
    set_y(y);
    set_dx(0);
    set_dy(0);
    textures = std::vector<SDL_Texture*>(size);
}
