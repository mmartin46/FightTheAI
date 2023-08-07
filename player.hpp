#ifndef PLAYER_H
#define PLAYER_H
#pragma once
#include "entity.hpp"


class Player : public Entity
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

        double damage;

        /*
        0000 - Idle
        0001 - Left
        0010 - Right
        0100 - Down
        1000 - Up
        */ 
        int keyPressed;
        int speedLimit;
        bool slowingDown, facingLeft, doAttack_0, doAttack_1;

        // Images
        std::vector<SDL_Texture*> textures;

    public:
        Player();
        Player(float, float);


        // Player Textures
        void setTexture(int idx, SDL_Texture *texture);
        inline SDL_Texture* getTexture(int idx) { return textures.at(idx); }




        
        // Movement
        inline void setSpeedLimit(int s) { speedLimit = s; }
        inline int  getSpeedLimit() { return speedLimit; }

        inline void setDoAttack_0() { doAttack_0 = true; }
        inline void resetDoAttack_0() { doAttack_0 = false; }

        inline void setDoAttack_1() { doAttack_1 = true; }
        inline void resetDoAttack_1() { doAttack_1 = false; }

        inline float getDamage() { return damage; }
        inline void setDamage(float d) { damage = d; }
        inline void incDamage() { damage += 0.2; }

        inline virtual void applyGravity() { set_dy(get_dy() + 0.5f); } // Accumulates the gravity constant to the player.
        inline virtual void applyJump() { dy -= 0.3f; }

        inline virtual void moveLeft(int v) { setFacingLeft(true); (get_x() - v); }
        inline virtual void moveRight(int v) { setFacingLeft(false); set_x(get_x() + v); }
        inline virtual void moveUp(int v) { set_y(get_y() - 1); }
        inline virtual void moveDown(int v) { set_y(get_y() + 1); }

        inline void resetKeys() { keyPressed = 0; }
        inline void setMovingLeft() {  resetKeys(); bitset::set_bit(keyPressed, 0); }
        inline void setMovingRight() { resetKeys(); bitset::set_bit(keyPressed, 1); }
        inline void setMovingDown() { resetKeys(); bitset::set_bit(keyPressed, 2); }
        inline void setMovingUp() { resetKeys(); bitset::set_bit(keyPressed, 3); }
        inline int getKeyPressed() { return keyPressed; }



        void leftMovement(float dist);
        void rightMovement(float dist);
        void downMovement();
        void upMovement(float dist);
        void animation(int time);

        inline virtual void slowMovement() { dx *= 0.8; }
        inline virtual void stopMovement() { dx = 0; }

        inline int getFrame() { return frame; }
        inline void setFrame(int f) { frame = f; }
        inline void incFrame() { ++frame;}

        inline virtual void setOnBlock() { onBlock = 1; }
        inline virtual void resetOnBlock() { onBlock = 0; }
        inline virtual int getOnBlock() { return onBlock; }

        // Player Animation

        inline virtual int getFacingLeft() { return facingLeft; } const
        inline virtual void setFacingLeft(int v) { facingLeft = v; }
        inline virtual bool getSlowingDown() { return slowingDown; } const
        inline virtual void setSlowingDown(bool s) { slowingDown = s; }

        SDL_Texture* operator[](int idx);
        void operator()(int idx, SDL_Texture *);
};  
#endif