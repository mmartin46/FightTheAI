#include "player.hpp"

class Enemy : public Player
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
        Distance target;
        /*
        0000 - Idle
        0001 - Left
        0010 - Right
        0100 - Down
        1000 - Up
        */ 
        int keyPressed;
        bool slowingDown, facingLeft, doAttack;

        // Images
        std::vector<SDL_Texture*> textures;
    public:
        template <typename T>
        void setupTarget(T &plyr);
        void movement();
};

template <typename T>
void Enemy::setupTarget(T &plyr)
{
    target.p1_x = plyr.get_x();
    target.p1_y = plyr.get_y();
    target.p2_x = get_x();
    target.p2_y = get_y();

}

void Enemy::movement()
{
    double heuristic = get_distances(&target);


}