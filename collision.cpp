#include "game.hpp"


/* 
Detects a collision between a player and a specific block,
and how the player is to be placed after the collision
*/
template <typename T>
int Game::mapCollision(T &plyr, Matrix<Entity> &blocks, int row, int col, int player_width, int player_height)
{
    int touched = 0;
    float pw = player_width, ph = player_height;
    float px = plyr.get_x(), py = plyr.get_y();
    float bx = blocks.at(row).at(col).get_x(), by = blocks.at(row).at(col).get_y(), bw = blocks.at(row).at(col).get_w(), bh = blocks.at(row).at(col).get_h();

    if (px+pw/2 > bx && px+pw/2 < bx+bw)
    {
        // Head Bump
        if (py < by+bh && py>by && plyr.get_dy() < 0)
        {
            // correct y
            plyr.set_y(by+bh);
            py = by+bh;

            // bumped our head, stop any jump velocity
            plyr.set_dy(0);
            plyr.resetOnBlock();
            touched = 1;
        }
    }
    if (px+pw > bx && px<bx+bw)
    {
        // Head bump
        if (py+ph > by && py < by && plyr.get_dy() > 0)
        {
            // correct y
            plyr.set_y(by-ph);
            py = by-ph;

            //landed on this ledge, stop any jump velocity
            plyr.set_dy(0);
            plyr.setOnBlock();
            touched = 2;
        }
    }

    if (py+ph > by && py<by+bh)
    {
        // Rubbing against right edge
        if (px < bx+bw && px+pw > bx+bw && plyr.get_dx() < 0)
        {
            // correct x
            plyr.set_x(bx+bw);
            px = bx+bw;

            plyr.set_dx(0);
            touched = 3;
        }
        // Rubbing against left edge
        else if (px+pw > bx && px < bx && plyr.get_dx() > 0)
        {
            // correct x
            plyr.set_x(bx-pw);
            px = bx-pw;

            plyr.set_dx(0);
            touched = 4;
        }
    }
    return touched;
}

/*
Manages all the collisions within
the map.
*/
void Game::collisionManager()
{
    int row, col = 0;
    for (row = 0; row < 100; ++row)
    {
        for (col = 0; col < 100; ++col)
        {
            if (this->layer1.at(row).at(col) == world::BLOCK)
            {
                mapCollision(*getPlayer(), *this->getBlocks(), row, col, 20, 30);
                mapCollision(*getShot(), *this->getBlocks(), row, col, 5, 5);
                mapCollision(*getEnemy(), *this->getBlocks(), row, col, 20, 30);
            }
        }
    }
}


void Game::enemyPlayerCollision(const Uint8* state)
{
    if (state[SDL_SCANCODE_Q])
    {
        getPlayer()->setDoAttack_0();
        if (collide2d(playerEnemyCollision))
        {
            attackedPlayer = getEnemy();
            allowSmokeAnimation();


            getEnemy()->incDamage();
            getEnemy()->setFunctionalityOff();
            if (getPlayer()->getFacingLeft())
            {
                getEnemy()->set_dx(-3 * getEnemy()->getDamage());
                getEnemy()->set_dy(-2 * getEnemy()->getDamage());
            }
            else
            {
                getEnemy()->set_dx(3 * getEnemy()->getDamage());
                getEnemy()->set_dy(-2 * getEnemy()->getDamage());                
            }
        }
    }    
    
    if (state[SDL_SCANCODE_DOWN])
    {
        getPlayer()->setMovingDown();
        if (collide2d(playerEnemyCollision))
        {
            attackedPlayer = getEnemy();
            allowSmokeAnimation();

            getEnemy()->incDamage();
            getEnemy()->setFunctionalityOff();
            if (getPlayer()->getFacingLeft())
            {
                getEnemy()->set_dx(-2 * getEnemy()->getDamage());
                getEnemy()->set_dy(-3 * getEnemy()->getDamage());
            }
            else
            {
                getEnemy()->set_dx(2 * getEnemy()->getDamage());
                getEnemy()->set_dy(-3 * getEnemy()->getDamage());                
            }
        }    

    }

    if (((getTime() % 50) == 0) && !getEnemy()->getFunctionality())
    {
        getEnemy()->setFunctionalityOn();
    }
}
