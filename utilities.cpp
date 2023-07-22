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
#include <sys/types.h>
using std::unordered_map;
using namespace std::chrono;

template <typename T>
using Matrix = std::vector<std::vector<T> >;
using std::pair;
using std::shared_ptr;
using std::vector;
using std::string;
using std::unordered_map;

// Utilies bit operations to save of space.
namespace bitset
{
   uint8_t get_bit(const int &value, int pos) 
   {
      return (value >> pos) & 1U;
   }

   void set_bit(int &value, int pos)
   {
      value |= (1 << pos);
   }
   void reset_bit(int &value, int pos)
   {
      value &= ~(1 << pos);
   }


}

int collide2d(float x1, float x2, float y1, float y2, float ht1, float wt1, float wt2, float ht2)
{
   return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}

bool notMovingHorizontally(const Uint8 *state)
{
   return (!state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT]);
}

bool notMovingVertically(const Uint8 *state)
{
   return (!state[SDL_SCANCODE_UP] && !state[SDL_SCANCODE_DOWN]);
}

// Counts the # of files within the directory
int getDirectorySize(const char *directName)
{
   DIR *dirPtr;
   int fileCount = 0;
   struct dirent *ep;
   dirPtr = opendir(directName);

   if (dirPtr == NULL)
   {
      perror("getDirectorySize() : No such directory found.\n");
   }
   else
   {
      while (ep = readdir(dirPtr))
      {
         ++fileCount;
      }
      static_cast<void>(closedir(dirPtr));
   }
   return fileCount;
}

/*
Utilizes the Manhattan distance to find
the distance between two positions.
*/
double get_distances(double x_1, double x_2, double y_1, double y_2)
{
   double val = abs(x_1 - x_2) + abs(y_1 - y_2);
   return val;
}

/*
Finds the minimum within an unordered map.
*/
template <class K, class V>
V mapMin(std::unordered_map<K, V> &mp)
{
   V min_elem = 0;
   typename std::unordered_map<K, V>::pointer ptr, end = mp.data() + mp.size();
   for (ptr = mp.data(); ptr < end; ++ptr)
   {
      if (min_elem > ptr->second)
      {  
         min_elem = ptr->second;
      }
   }
   return min_elem;
}

/*
Gets the image dimensions.
\param filePath path to the image.

\return pair.first -> width

\return pair.second -> height

https://stackoverflow.com/questions/5354459/
c-how-to-get-the-image-size-of-a-png-file-in-directory
*/
pair<int, int> getImageDimensions(const char *filePath)
{
   pair<int, int> dim;
   unsigned char buffer[8];

   std::ifstream input(filePath);
   input.seekg(16);
   input.read(reinterpret_cast<char*>(&buffer), 8);

   dim.first = (buffer[4] << 24) + (buffer[5] << 16) + (buffer[6] << 8) + (buffer[7] << 0);
   dim.second = (buffer[0] << 24) + (buffer[1] << 16) + (buffer[2] << 8) + (buffer[3] << 0);

   return dim;
}


// Finds the distance between
// two points.
typedef struct {
   int p1_x;
   int p1_y;
   int p2_x;
   int p2_y;
} Distance;

struct comp
{
   template <typename T>
   bool operator() (const T&lhs, const T&rhs)
   {
      return lhs.second < rhs.second;
   }
};
