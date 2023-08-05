#include "game.hpp"


#ifndef GETFRAME
    // Gets the frame of an object
    #define GETFRAME(object) object[object.getFrame()]
#endif

#ifndef SCROLLABLE
    #define SCROLLABLE(object, scroll, z) \
    static_cast<int>(scroll + object->z) 
#endif

void Game::render()
{
    SDL_SetRenderDrawColor(this->getRenderer(), 120, 120, 120, 255);
    SDL_RenderClear(this->getRenderer());
    SDL_Rect rect;

    // Background
    rect = { static_cast<int>((this->getScrollX() / 200) + getBackground()->get_x()), static_cast<int>((this->getScrollY() / 20) + getBackground()->get_y()), getBackground()->get_w(), getBackground()->get_h() };
    SDL_RenderCopy(this->getRenderer(), getBackground()->getTexture(0), NULL, &rect);


    int x, y;
    for (x = 0; x < 100; ++x)
    {
        for (y = 0; y < 100; ++y)
        {
            switch(layer1.at(x).at(y))
            {
                case world::BLOCK : {
                    rect = { static_cast<int>(getScrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(getScrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
                    SDL_RenderCopy(this->getRenderer(), getBlockTexture(), NULL , &rect);
                } break;
            }
        }
    }

    // Shot
    rect = { SCROLLABLE(getShot(), getScrollX(), get_x()), SCROLLABLE(getShot(), getScrollY(), get_y()), getShot()->get_h(), getShot()->get_w() };
    SDL_RenderCopy(this->getRenderer(), getShotTexture(), NULL, &rect);

    // Player
    rect = { SCROLLABLE(getPlayer(), getScrollX(), get_x()), SCROLLABLE(getPlayer(), getScrollY(), get_y()), getPlayer()->get_h(), getPlayer()->get_w() };
    SDL_RenderCopyEx(this->getRenderer(), GETFRAME(player), NULL, &rect, 0, NULL, (SDL_RendererFlip)(getPlayer()->getFacingLeft() == true));

    // Enemy
    rect = { SCROLLABLE(getEnemy(), getScrollX(), get_x()), SCROLLABLE(getEnemy(), getScrollY(), get_y()), getEnemy()->get_h(), getEnemy()->get_w() };
    SDL_RenderCopyEx(this->getRenderer(), GETFRAME(enemy), NULL, &rect, 0, NULL, (SDL_RendererFlip) (getEnemy()->getFacingLeft() == true));

    renderGameStatsBar(rect);
    makeSmokeRect(rect, attackedPlayer);


    playerEnemyCollision->x1 = player.get_x();
    playerEnemyCollision->y1 = player.get_y();
    playerEnemyCollision->wt1 = player.get_w();
    playerEnemyCollision->ht1 = player.get_h(); 

    playerEnemyCollision->x2 = enemy.get_x();
    playerEnemyCollision->y2 = enemy.get_y();
    playerEnemyCollision->wt2 = enemy.get_w();
    playerEnemyCollision->ht2 = enemy.get_h(); 


    SDL_RenderPresent(this->getRenderer());
}


template <typename T>
void Game::makeSmokeRect(SDL_Rect rect, T *plyr) 
{
    rect = { static_cast<int>(getScrollX() + plyr->get_x()), static_cast<int>(getScrollY() + plyr->get_y()), plyr->get_h(), plyr->get_w() };
    SDL_RenderCopyEx(this->getRenderer(), getSmoke()->getTexture(getSmoke()->getFrame()), NULL, &rect, 0, NULL, (SDL_RendererFlip)(plyr->getFacingLeft() == true));
}


void Game::renderGameStatsBar(SDL_Rect &rect)
{
    rect = { 0, 0, gameStatsBar.get_w(), gameStatsBar.get_h() };
    SDL_RenderCopy(this->getRenderer(), gameStatsBar.getTexture(0), NULL, &rect);
}

