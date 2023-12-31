#ifndef CONSTANTS_H
#define CONSTANTS_H
#pragma once

#define BLOCK_WIDTH 20
#define BLOCK_HEIGHT 20

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


#define SCREEN_WIDTH 420
#define SCREEN_HEIGHT 236

#define GRAVITY 0.5f
#define PLAYERSPEED 0.5f
#define PLAYERSPEEDDX 3
#define PLAYERJUMPHEIGHT -11

#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 30

#define ENEMY_WIDTH 20
#define ENEMY_HEIGHT 30

#define BLOCK_WIDTH 20
#define BLOCK_HEIGHT 20

#define SHOT_WIDTH 5
#define SHOT_HEIGHT 5

#define MAP_WIDTH 100
#define MAP_HEIGHT 100


#define IDLE 0
#define LEFT 1
#define RIGHT 2
#define DOWN 4
#define UP 8

#ifndef GETFRAME
    // Gets the frame of an object
    #define GETFRAME(object) object[object.getFrame()]
#endif

#ifndef SCROLL
    // Scrolls the background
    #define SCROLL(object, scroll, z) \
    static_cast<int>(scroll + object.z) 
#endif

#ifndef ISFACINGLEFT
    // Checks if the object is facing left.
    #define ISFACINGLEFT(object) (SDL_RendererFlip) (object->getFacingLeft() == true)
#endif

#ifndef BLOCKS
    // Quick way to access the matrix of blocks
    #define BLOCKS(x, y) blocks.at(x).at(y) 
#endif

#endif