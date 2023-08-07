#ifndef ENEMY_H
#define ENEMY_H
#pragma once
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

        bool functionality;

        Distance target;
        std::unordered_map<std::string, double> states;
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
        Enemy();

        void setupTarget(Player &plyr);
        void movement();

        inline void setFunctionalityOn() { functionality = 1; }
        inline void setFunctionalityOff() { functionality = 0; }
        inline int getFunctionality() { return functionality; }

        bool usePunchAttack(const CollisionStruct &collision, Player *plyr);
        bool useSpinAttack(const CollisionStruct &collision, Player *plyr);
};


#endif