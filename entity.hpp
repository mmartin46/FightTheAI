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
        int w, h;
        float dx, dy;
        int frame;
        std::vector<SDL_Texture*> textures;
        
    public:
        Entity();
        Entity(float x, float y, unsigned int size);
        inline virtual float get_x() { return x; }
        inline virtual void set_x(float v) { x = v; }
        inline virtual float get_y() { return y; }
        inline virtual void set_y(float v) { y = v; }
        inline virtual float get_dx() { return dx; }
        inline virtual void set_dx(float v) { dx = v; }
        inline virtual float get_dy() { return dy; }
        inline virtual void set_dy(float v) { dy = v; }

        inline virtual int get_w() { return w; }
        inline virtual void set_w(int v) { w = v; }
        inline virtual int get_h() { return h; }
        inline virtual void set_h(int v) { h = v; }

        virtual void setTexture(int idx, SDL_Texture *texture);
        inline SDL_Texture* getTexture(int idx) { return textures.at(idx); }


        inline virtual void setFrame(int f) { frame = f; }
        inline virtual int getFrame() { return frame; }

};


Entity::Entity()
{
    this->set_x(0);
    this->set_y(0);
    textures = std::vector<SDL_Texture*>(30);
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


