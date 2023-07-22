#pragma once
#include "utilities.cpp"
/*
A simple Entity Class
*/
class Entity 
{
    private:
      /* data */
      int x, y, w, h;
      float dx, dy;
      int frame;
      std::vector<SDL_Texture*> sprites;
    public:
        Entity();
        Entity(int x, int y, int size);
        inline int get_x() { return x; }
        inline void set_x(int v) { x = v; }
        inline int get_y() { return y; }
        inline void set_y(int v) { y = v; }
        inline float get_dx() { return dx; }
        inline void set_dx(float v) { dx = v; }
        inline float get_dy() { return dy; }
        inline void set_dy(float v) { dy = v; }

        inline int get_w() { return w; }
        inline void set_w(int v) { w = v; }
        inline int get_h() { return h; }
        inline void set_h(int v) { h = v; }

        inline void setSprite(int idx, SDL_Texture* sprite) { sprites.at(idx) = sprite; }
        inline SDL_Texture* getSprite(int idx) { return sprites.at(idx); }

        inline void setFrame(int f) { frame = f; }
        inline int getFrame() { return frame; }
};


Entity::Entity()
{
    this->set_x(0);
    this->set_y(0);
    sprites = std::vector<SDL_Texture*>(1);
    this->setFrame(0);    
}

Entity::Entity(int x, int y, int size)
{
    this->set_x(x);
    this->set_y(y);
    sprites = std::vector<SDL_Texture*>(size);
    this->setFrame(0);
}
