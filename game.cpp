#include "game.hpp"
#include "animation.cpp"
#include "render.cpp"
#include "collision.cpp"
#include "loader.cpp"
#include "events.cpp"

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

