#include "player.hpp"

// Returns a texture
SDL_Texture* Player::operator[](int idx)
{
    // If the index out of range.
    if (idx >= textures.size() || idx < 0)
    {
        std::cout << "operator[]: Invalid Index\n";
        SDL_Quit();
        exit(1);
    }

    return textures.at(idx);
}

void Player::operator() (int idx, SDL_Texture *texture)
{
    // If the index out of range.
    if (idx >= textures.size() || idx < 0)
    {
        std::cout << "operator(): Invalid Index\n";
        SDL_Quit();
        exit(1);
    }
    textures.at(idx) = texture; 
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



