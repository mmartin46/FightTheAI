#pragma once



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

        bool slowingDown, facingLeft;
        // Images
        std::vector<SDL_Texture*> textures;

    public:
        Player();
        Player(float, float);


        // Player Textures
        void setTexture(int idx, SDL_Texture *texture);
        inline SDL_Texture* getTexture(int idx) { return textures.at(idx); }

        
        // Movement
        inline virtual void applyGravity() { set_dy(get_dy() + 0.5f); } // Accumulates the gravity constant to the player.
        inline virtual void applyJump() { dy -= 0.3f; }

        inline virtual void moveLeft(int v) { set_x(get_x() - v); }
        inline virtual void moveRight(int v) { set_x(get_x() + v); }
        inline virtual void moveUp(int v) { set_y(get_y() - 1); }
        inline virtual void moveDown(int v) { set_y(get_y() + 1); }

        void leftMovement(int dist);
        void rightMovement(int dist);
        void downMovement();
        void upMovement(int dist);

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

void Player::leftMovement(int dist)
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
void Player::rightMovement(int dist)
{
    set_dx(get_dx() + PLAYERSPEED);
    if (get_dx() > dist)
    {
        set_dx(PLAYERSPEEDDX);
    }
    this->setFacingLeft(true);
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

void Player::upMovement(int dist)
{
    if (getOnBlock())
    {
        set_dy(dist);
        resetOnBlock();
    }
}

Player::Player()
{
    this->set_x(0);
    this->set_y(0);
    this->set_dx(0);
    this->set_dy(0);
    textures = std::vector<SDL_Texture*>(30);

    this->resetOnBlock();
    this->setFrame(0);
    this->setFacingLeft(true);
    this->setSlowingDown(false);
}

Player::Player(float x, float y)
{
    this->set_x(x);
    this->set_y(y);
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



