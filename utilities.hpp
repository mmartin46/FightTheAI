#ifndef UTILITIES_H
#define UTILITIES_H
#pragma once
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_mixer.h>
#include <SDL2\SDL_ttf.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <utility>
#include <cstdlib>
#include <unordered_map>
#include <algorithm>
#include <future>
#include <dirent.h>
#include <chrono>
#include <thread>
#include <sys/types.h>
#include "constants.hpp"
using std::unordered_map;
using namespace std::chrono;



template <typename T>
using Matrix = std::vector<std::vector<T> >;
using std::pair;
using std::shared_ptr;
using std::vector;
using std::string;
using std::unordered_map;


// Finds the distance between
// two points.
typedef struct {
   int p1_x;
   int p1_y;
   int p2_x;
   int p2_y;
} Distance;

typedef struct
{
   template <typename T>
   bool operator() (const T&lhs, const T&rhs)
   {
      return lhs.second < rhs.second;
   }
} comp;


template <typename T, typename U>
struct entitysize_pair_ {
   T first;
   U second;
};



// Utilies bit operations to save of space.
namespace bitset
{
   extern uint8_t get_bit(const int &value, int pos);

   extern void set_bit(int &value, int pos);
   extern void reset_bit(int &value, int pos);
}


bool inclusive_range(int start, int end, int time);


typedef struct {
   float x1;
   float x2;
   float y1;
   float y2; 
   float wt1;
   float wt2;
   float ht1;
   float ht2;
} CollisionStruct;

int collide2d(float x1, float x2, float y1, float y2, float ht1, float wt1, float wt2, float ht2);

int collide2d(const CollisionStruct *c);


bool notMovingHorizontally(const Uint8 *state);

bool notMovingVertically(const Uint8 *state);

// Counts the # of files within the directory
int getDirectorySize(const char *directName);

/*
Utilizes the Manhattan distance to find
the distance between two positions.
*/
double get_distances(double x_1, double x_2, double y_1, double y_2);
/*
Utilizes the Manhattan distance to find
the distance between two positions.
*/
double get_distances(Distance *target);

/*
Finds the minimum within an unordered map.
*/
template <class K, class V>
V mapMin(std::unordered_map<K, V> &mp);
/*
Gets the image dimensions.
\param filePath path to the image.

\return pair.first -> width

\return pair.second -> height

https://stackoverflow.com/questions/5354459/
c-how-to-get-the-image-size-of-a-png-file-in-directory
*/
pair<int, int> getImageDimensions(const char *filePath);

#endif