#pragma once
#include "utilities.hpp"
/*
A simple Entity Class
*/
class Entity 
{
    private:
        /* data */
        float x, y;
        int w, h;
        float dx, dy;
        int frame;
        std::vector<SDL_Texture*> textures;
    public:
        Entity();
        Entity(float x, float y, unsigned int size);
        inline float get_x() { return x; }
        inline void set_x(float v) { x = v; }
        inline float get_y() { return y; }
        inline void set_y(float v) { y = v; }
        inline float get_dx() { return dx; }
        inline void set_dx(float v) { dx = v; }
        inline float get_dy() { return dy; }
        inline void set_dy(float v) { dy = v; }

        inline int get_w() { return w; }
        inline void set_w(int v) { w = v; }
        inline int get_h() { return h; }
        inline void set_h(int v) { h = v; }

        virtual void setTexture(int idx, SDL_Texture *texture);
        inline SDL_Texture* getTexture(int idx) { return textures.at(idx); }


        inline void setFrame(int f) { frame = f; }
        inline int getFrame() { return frame; }
};


