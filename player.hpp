#pragma once
#include "entity.hpp"


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

        double damage;

        /*
        0000 - Idle
        0001 - Left
        0010 - Right
        0100 - Down
        1000 - Up
        */ 
        int keyPressed;
        int speedLimit;
        bool slowingDown, facingLeft, doAttack_0, doAttack_1;

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

        inline void setDoAttack_0() { doAttack_0 = true; }
        inline void resetDoAttack_0() { doAttack_0 = false; }

        inline void setDoAttack_1() { doAttack_1 = true; }
        inline void resetDoAttack_1() { doAttack_1 = false; }

        inline float getDamage() { return damage; }
        inline void setDamage(float d) { damage = d; }
        inline void incDamage() { damage += 0.2; }

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

        SDL_Texture* operator[](int idx);
};  

SDL_Texture* Player::operator[](int idx)
{
    return textures.at(idx);
}


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
        else if (doAttack_0 == true)
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
    setDamage(1);
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



