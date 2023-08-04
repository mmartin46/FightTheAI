#include "game.hpp"
#include "animation.cpp"
#include "render.cpp"
#include "collision.cpp"
#include "loader.cpp"

Game::Game()
{
    setTime(0);
    setScrollX(0);
    setScrollY(0);

    setScreenHeight(SCREEN_HEIGHT);
    setScreenWidth(SCREEN_WIDTH);

    getPlayer()->set_x(200);
    getPlayer()->set_y(200);
    getPlayer()->set_dx(0);
    getPlayer()->set_dy(0);

    getEnemy()->set_x(200);
    getEnemy()->set_y(200);
    getEnemy()->set_dx(0);
    getEnemy()->set_dy(0);

    getBackground()->set_x(0);
    getBackground()->set_y(0);
    getBackground()->set_w(420);
    getBackground()->set_h(240);

    getSmoke()->setFrame(4);

    attackedPlayer = getPlayer();
    layer1 = Matrix<int>(100, vector<int>(100));
    blocks = Matrix<Entity>(100, vector<Entity>(100));
}


// Make the shot position match a specific player
void Game::matchShotPosition(Player *player)
{
    getShot()->set_x(player->get_x() + 10);
    getShot()->set_y(player->get_y() + 5);
}




void Game::eventHandler(SDL_Window *window, SDL_Event &event, int &done)
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_WINDOWEVENT_CLOSE:
            {
                if (window)
                {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = 1;
                }
            }
            break;
            case SDL_QUIT:
                done = 1;
            break;
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        done = 1;
                    break;
                    case SDLK_UP:
                        if (getPlayer()->getOnBlock())
                        {
                            getPlayer()->set_dy(static_cast<float>(PLAYERJUMPHEIGHT));
                            getPlayer()->resetOnBlock();
                        }
                }
            }
            break;
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    // Attacks
    if (state[SDL_SCANCODE_SPACE])
    {
        shotMovement();
    }

    // Camera
    if (state[SDL_SCANCODE_W])
    {
        zoomOut();
    }
    else if (state[SDL_SCANCODE_S])
    {
        zoomIn();
    }



    if (state[SDL_SCANCODE_UP])
    {
        getPlayer()->setMovingUp();
        getPlayer()->applyJump();
    }
    if (state[SDL_SCANCODE_LEFT])
    {
        getPlayer()->setMovingLeft();
        getPlayer()->leftMovement(3);
    }
    else if (state[SDL_SCANCODE_RIGHT])
    {
        getPlayer()->setMovingRight();
        getPlayer()->rightMovement(3);
    }
    else
    {
        getPlayer()->resetDoAttack_0();
        getPlayer()->resetDoAttack_1();
        if (getPlayer()->get_dy() != 0)
        {
            getPlayer()->resetKeys();
        }
        getPlayer()->downMovement();
    }

    enemyPlayerCollision(state);
}

void Game::initGameStatsBar()
{
   char str[200] = "";
   sprintf(str, "Player 1: %d%     Player 2: %d%        Time: %u             ", (int)(getPlayer()->getDamage() * 10), (int)(getEnemy()->getDamage() * 10), (this->getTime()));

   SDL_Color white = { 255, 255, 255, 255 };
   SDL_Surface *tmp = TTF_RenderText_Blended(this->getFont(), str, white);
   gameStatsBar.set_w(tmp->w);
   gameStatsBar.set_h(tmp->h);
   gameStatsBar.setTexture(0, SDL_CreateTextureFromSurface(this->getRenderer(), tmp));
   SDL_FreeSurface(tmp);
}




void Game::shotMovement()
{
    switch (getShot()->getDidShoot())
    {
        case status::DIDSHOOT : {
            getShot()->resetDidShoot();
            break;
        }
        case status::DIDNTSHOOT : {
            getShot()->setDidShoot();
            break;
        }
    }
}