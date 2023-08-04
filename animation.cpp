#include "game.hpp"

void Game::smokeAnimation()
{
    if (getSmokeAnimationState() == true)
    {
        if ((time % 10) < 10)
        {
            if ((time % 10) < 3.5)
            {
                getSmoke()->setFrame(0);
            }
            else if ((time % 10) >= 3.5 && (time % 20) < 5)
            {
                getSmoke()->setFrame(1);
            }
            else if ((time % 10) >= 5 && (time % 20) < 7.5)
            {
                getSmoke()->setFrame(2);
            }
            else if ((time % 10) >= 7.5 && (time % 10) < 10)
            {
                getSmoke()->setFrame(3);
            }
            else
            {
                disallowSmokeAnimation();
                getSmoke()->setFrame(4);
            }
        }
    }
}

void Game::animate()
{
    initGameStatsBar();
    // Timer
    setTime(getTime() + 1);

    // Set Enemy's Target
    getEnemy()->setupTarget(*getPlayer());

    // Player Movement
    getPlayer()->set_x(getPlayer()->get_x() + getPlayer()->get_dx());
    getPlayer()->set_y(getPlayer()->get_y() + getPlayer()->get_dy());

    getEnemy()->set_x(getEnemy()->get_x() + getEnemy()->get_dx());
    getEnemy()->set_y(getEnemy()->get_y() + getEnemy()->get_dy());

    //Shot Positioning
    if (getShot()->getDidShoot() == status::DIDNTSHOOT)
    {
        matchShotPosition(getPlayer());
    }
    else
    {
        getShot()->set_x(getShot()->get_x() + 1);
        getShot()->set_dx(getShot()->get_dx() + 0.5);
    }


    getPlayer()->animation(getTime());

    // Enemy Attacks
    getEnemy()->movement();
    
    
    if (getEnemy()->usePunchAttack(*playerEnemyCollision, getPlayer()))
    {
        attackedPlayer = getPlayer();
        allowSmokeAnimation();
        smokeAnimation();
    }
    if (getEnemy()->useSpinAttack(*playerEnemyCollision, getPlayer()))
    {
        attackedPlayer = getPlayer();
        allowSmokeAnimation();
        smokeAnimation();
    }

    getEnemy()->animation(getTime());



    getShot()->applyGravity();

    // Gravity
    getPlayer()->applyGravity();
    getEnemy()->applyGravity();

    // Scrolling
    this->setScrollX(-getPlayer()->get_x() + getScreenWidth() / 2);
    this->setScrollY(-getPlayer()->get_y() + getScreenHeight() / 2);

}

