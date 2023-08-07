#ifndef SHOT_H
#define SHOT_H
#pragma once
#include "player.hpp"

enum class status {
    DIDSHOOT,
    DIDNTSHOOT 
};


class Shot : public Player
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
        int timer;

        status shotStatus; 
        // Images
        std::vector<SDL_Texture*> textures;
    public:
        Shot();
        Shot(int x, int y, unsigned int size);
        status getDidShoot() { return shotStatus; }
        inline void resetDidShoot() { shotStatus = status::DIDNTSHOOT; }
        inline void setDidShoot() { shotStatus = status::DIDSHOOT; }

        inline int getTimer() { return timer; }
        inline void startTimer() { ++timer; }
        inline void resetTimer() { timer = 0; }
};


#endif