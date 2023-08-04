#include "game.hpp"


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