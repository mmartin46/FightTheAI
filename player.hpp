#pragma once
#include "entity.hpp"



#define IDLE 0
#define LEFT 1
#define RIGHT 2
#define DOWN 4
#define UP 8


class Player : public Entity
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
        int speedLimit;
        bool slowingDown, facingLeft, doAttack;

        // Images
        std::vector<SDL_Texture*> textures;

    public:
        Player();
        Player(float, float);


        // Player Textures
        void setTexture(int idx, SDL_Texture *texture);
        inline SDL_Texture* getTexture(int idx) { return textures.at(idx); }




        
        // Movement
        inline void setSpeedLimit(int s) { speedLimit = s; }
        inline int  getSpeedLimit() { return speedLimit; }

        inline void setDoAttack() { doAttack = true; }
        inline void resetDoAttack() { doAttack = false; }

        inline virtual void applyGravity() { set_dy(get_dy() + 0.5f); } // Accumulates the gravity constant to the player.
        inline virtual void applyJump() { dy -= 0.3f; }

        inline virtual void moveLeft(int v) { setFacingLeft(true); (get_x() - v); }
        inline virtual void moveRight(int v) { setFacingLeft(false); set_x(get_x() + v); }
        inline virtual void moveUp(int v) { set_y(get_y() - 1); }
        inline virtual void moveDown(int v) { set_y(get_y() + 1); }

        inline void resetKeys() { keyPressed = 0; }
        inline void setMovingLeft() {  resetKeys(); bitset::set_bit(keyPressed, 0); }
        inline void setMovingRight() { resetKeys(); bitset::set_bit(keyPressed, 1); }
        inline void setMovingDown() { resetKeys(); bitset::set_bit(keyPressed, 2); }
        inline void setMovingUp() { resetKeys(); bitset::set_bit(keyPressed, 3); }
        inline int getKeyPressed() { return keyPressed; }



        void leftMovement(float dist);
        void rightMovement(float dist);
        void downMovement();
        void upMovement(float dist);
        void animation(int time);

        inline virtual void slowMovement() { dx *= 0.8; }
        inline virtual void stopMovement() { dx = 0; }

        inline int getFrame() { return frame; }
        inline void setFrame(int f) { frame = f; }
        inline void incFrame() { ++frame;}

        inline virtual void setOnBlock() { onBlock = 1; }
        inline virtual void resetOnBlock() { onBlock = 0; }
        inline virtual int getOnBlock() { return onBlock; }

        // Player Animation

        inline virtual int getFacingLeft() { return facingLeft; } const
        inline virtual void setFacingLeft(int v) { facingLeft = v; }
        inline virtual bool getSlowingDown() { return slowingDown; } const
        inline virtual void setSlowingDown(bool s) { slowingDown = s; }

};  



void Player::animation(int time)
{
    time = (time % 20);

    if (time < 20 && (get_dx() != 0))
    {
        if (time <= 3.5)
        {
            setFrame(0);
        }

        else if (inclusive_range(3.5, 5, time))
        {
            setFrame(1);
        }
        else if (inclusive_range(5, 7.5, time))
        {
            setFrame(2);
        }
        else if (inclusive_range(7.5, 10, time))
        {
            setFrame(3);
        }
        else if (inclusive_range(10, 13.5, time))
        {
            setFrame(4);
        }
        else if (inclusive_range(13.5, 15, time))
        {
            setFrame(5);
        }
        else if (inclusive_range(15, 17.5, time))
        {
            setFrame(6);
        }
        else
        {
            setFrame(7);
        }
    }
    else
    {
        if (getKeyPressed() == DOWN)
        {
            if (time < 20 )
            {
                if (time <= 5)
                {
                    setFrame(8);
                }

                else if (inclusive_range(5, 8.5, time))
                {
                    setFrame(9);
                }
                else if (inclusive_range(8.5, 11.5, time))
                {
                    setFrame(10);
                }
                else if (inclusive_range(11.5, 14.5, time))
                {
                    setFrame(11);
                }
                else if (inclusive_range(14.5, 18, time))
                {
                    setFrame(12);
                }
                else
                {
                    setFrame(13);
                }
            }            
        }
        else if (doAttack == true)
        {
            if (time < 20 )
            {
                if (time <= 5)
                {
                    setFrame(14);
                }

                else if (inclusive_range(5, 8.5, time))
                {
                    setFrame(15);
                }
                else if (inclusive_range(8.5, 11.5, time))
                {
                    setFrame(16);
                }
                else if (inclusive_range(11.5, 14.5, time))
                {
                    setFrame(17);
                }
                else if (inclusive_range(14.5, 18, time))
                {
                    setFrame(18);
                }
                else
                {
                    setFrame(17);
                }
            }   
        }
        else
        {
            setFrame(0);
        }
    }
}

void Player::leftMovement(float dist)
{
    set_dx(get_dx() + -PLAYERSPEED);
    if (get_dx() < -dist)
    {
       set_dx(-PLAYERSPEEDDX);
    }
    this->setFacingLeft(true);
    this->setSlowingDown(false);
}

// Applys right movement
// If the player dx is less than
// the "dist" variable increase
// dx by the PLAYERSPEED macro
void Player::rightMovement(float dist)
{
    set_dx(get_dx() + PLAYERSPEED);
    if (get_dx() > dist)
    {
        set_dx(PLAYERSPEEDDX);
    }
    this->setFacingLeft(false);
    this->setSlowingDown(false);
}

void Player::downMovement()
{
    set_dx(get_dx() * 0.8);
    setSlowingDown(true);
    if (SDL_fabsf(get_dx()) < 0.1f)
    {
        set_dx(0);
    }
}

void Player::upMovement(float dist)
{
    if (getOnBlock())
    {
        set_dy(dist);
        resetOnBlock();
    }
}

Player::Player()
{
    keyPressed = 0;
    this->set_x(0);
    this->set_y(0);
    this->set_dx(0);
    this->set_dy(0);
    textures = std::vector<SDL_Texture*>(30);

    this->resetOnBlock();
    this->setSpeedLimit(PLAYERSPEED);
    this->setFrame(0);
    this->setFacingLeft(true);
    this->setSlowingDown(false);
}

Player::Player(float x, float y)
{
    this->set_x(x);
    this->set_y(y);
    this->setSpeedLimit(PLAYERSPEED);
    textures = std::vector<SDL_Texture*>(30);
}


void Player::setTexture(int idx, SDL_Texture *texture)
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



