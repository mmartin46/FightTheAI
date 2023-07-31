#include "player.hpp"

class Enemy : public Player
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
        /*
        0000 - Idle
        0001 - Left
        0010 - Right
        0100 - Down
        1000 - Up
        */ 
        int keyPressed;
        bool slowingDown, facingLeft, doAttack;

        // Images
        std::vector<SDL_Texture*> textures;
    public:
        void movement();
};