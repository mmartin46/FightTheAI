#pragma once
#include "entity.hpp"

#define GRAVITY 0.8
#define PLAYERSPEEDLIMIT 6
#define PLAYERSPEEDDX 6

class Player : public Entity
{
    private:
        /* data */
        float x, y;
        float dx, dy;
        int onBlock;
        bool landed;
        int animFrame;

        bool slowingDown, facingLeft;
        // Images
        std::vector<SDL_Texture*> textures;

    public:
        Player();
        Player(int, int);


        // Player Textures
        void setPlayerTexture(int idx, SDL_Texture *texture);
        inline SDL_Texture* getPlayerTexture(int idx) { return textures.at(idx); }
        
        // Movement
        inline virtual void apply_gravity() { dy += GRAVITY; } // Accumulates the gravity constant to the player.
                
        inline virtual void moveLeft() { dx += -PLAYERSPEEDLIMIT; }
        inline virtual void moveRight() { dx += PLAYERSPEEDLIMIT; }

        inline virtual void set_left_dx() { dx = -PLAYERSPEEDDX; }
        inline virtual void set_right_dx() { dx = PLAYERSPEEDDX; }

        inline virtual void slowMovement() { dx *= 0.8; }
        inline virtual void stopMovement() { dx = 0; }

        inline virtual void setOnBlock() { onBlock = 1; }
        inline virtual void resetOnBlock() { onBlock = 0; }
        inline virtual int getOnBlock() { return onBlock; }

        // Player Animation

        inline virtual int getFacingLeft() { return facingLeft; } const
        inline virtual void setFacingLeft(int v) { facingLeft = v; }
        inline virtual bool getSlowingDown() { return slowingDown; } const
        inline virtual void setSlowingDown(bool s) { slowingDown = s; }
};  


Player::Player()
{
    this->set_x(0);
    this->set_y(0);
    this->set_dx(0);
    this->set_dy(0);
    textures = std::vector<SDL_Texture*>(30);
}

Player::Player(int x, int y)
{
    this->set_x(x);
    this->set_y(y);
    textures = std::vector<SDL_Texture*>(30);
}


void Player::setPlayerTexture(int idx, SDL_Texture *texture)
{
    // If the index out of range.
    if (idx >= textures.size() || idx < 0)
    {
        std::cout << "setPlayerTexture(): Invalid Index\n";
        SDL_Quit();
        exit(1);
    }
    // Set the texture
    textures.at(idx) = texture;
}