#include "game.hpp"




void Game::render()
{
    SDL_SetRenderDrawColor(this->getRenderer(), 120, 120, 120, 255);
    SDL_RenderClear(this->getRenderer());
    SDL_Rect rect;

    // Background
    rect = { SCROLL((*getBackground()), (this->getScrollX() / 200), get_x()), SCROLL((*getBackground()), (this->getScrollY() / 20), get_y()), getBackground()->get_w(), getBackground()->get_h() };
    SDL_RenderCopy(this->getRenderer(), getBackground()->getTexture(0), NULL, &rect);


    int x, y;
    for (x = 0; x < MAP_WIDTH; ++x)
    {
        for (y = 0; y < MAP_HEIGHT; ++y)
        {
            switch(layer1.at(x).at(y))
            {
                case world::BLOCK : {
                    rect = { SCROLL(BLOCKS(x, y), getScrollX(), get_x()), SCROLL(BLOCKS(x, y), getScrollY(), get_y()), BLOCKS(x, y).get_w(), BLOCKS(x, y).get_h() };
                    SDL_RenderCopy(this->getRenderer(), getBlockTexture(), NULL , &rect);
                } break;
            }
        }
    }

    // Shot
    rect = { SCROLL((*getShot()), getScrollX(), get_x()), SCROLL((*getShot()), getScrollY(), get_y()), getShot()->get_h(), getShot()->get_w() };
    SDL_RenderCopy(this->getRenderer(), getShotTexture(), NULL, &rect);

    // Player
    rect = { SCROLL((*getPlayer()), getScrollX(), get_x()), SCROLL((*getPlayer()), getScrollY(), get_y()), getPlayer()->get_h(), getPlayer()->get_w() };
    SDL_RenderCopyEx(this->getRenderer(), GETFRAME(player), NULL, &rect, 0, NULL, ISFACINGLEFT(getPlayer()));

    // Enemy
    rect = { SCROLL((*getEnemy()), getScrollX(), get_x()), SCROLL((*getEnemy()), getScrollY(), get_y()), getEnemy()->get_h(), getEnemy()->get_w() };
    SDL_RenderCopyEx(this->getRenderer(), GETFRAME(enemy), NULL, &rect, 0, NULL, ISFACINGLEFT(getEnemy()));

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
    rect = { SCROLL((*plyr), getScrollX(), get_x()), SCROLL((*plyr), getScrollY(), get_y()), plyr->get_h(), plyr->get_w() };
    SDL_RenderCopyEx(this->getRenderer(), getSmoke()->getTexture(getSmoke()->getFrame()), NULL, &rect, 0, NULL, ISFACINGLEFT(getPlayer()));
}


void Game::renderGameStatsBar(SDL_Rect &rect)
{
    rect = { 0, 0, gameStatsBar.get_w(), gameStatsBar.get_h() };
    SDL_RenderCopy(this->getRenderer(), gameStatsBar.getTexture(0), NULL, &rect);
}

