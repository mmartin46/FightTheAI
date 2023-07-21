#pragma once
#include "utilities.cpp"
/*
A simple Entity Class
*/
class Entity 
{
    private:
      /* data */
      float x, y;
      float dx, dy;
      int frame;
      std::vector<SDL_Texture*> sprites;
    public:
        Entity();
        Entity(float x, float y, int size);
        inline float get_x() { return x; }
        inline void set_x(float v) { x = v; }
        inline float get_y() { return y; }
        inline void set_y(float v) { y = v; }
        inline float get_dx() { return dx; }
        inline void set_dx(float v) { dx = v; }
        inline float get_dy() { return dy; }
        inline void set_dy(float v) { dy = v; }

        inline void setSprite(int idx, SDL_Texture* sprite) { sprites.at(idx) = sprite; }
        inline SDL_Texture* getSprite(int idx) { return sprites.at(idx); }

        inline void setFrame(int f) { frame = f; }
        inline int getFrame() { return frame; }

        SDL_Texture& operator[] (int idx);
};


Entity::Entity()
{
    this->set_x(0);
    this->set_y(0);
    sprites = std::vector<SDL_Texture*>(1);
    this->setFrame(0);    
}

Entity::Entity(float x, float y, int size)
{
    this->set_x(x);
    this->set_y(y);
    sprites = std::vector<SDL_Texture*>(size);
    this->setFrame(0);
};

SDL_Texture& Entity::operator[] (int idx)
{
    return *sprites.at(idx);
}