#include "utilities.hpp"


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


bool inclusive_range(int start, int end, int time)
{
    return (((time) > start) && ((time) <= end));
}



int collide2d(float x1, float x2, float y1, float y2, float ht1, float wt1, float wt2, float ht2)
{
   return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}

int collide2d(const CollisionStruct *c)
{
   return (!((c->x1 > (c->x2+c->wt2)) || (c->x2 > (c->x1+c->wt1)) || (c->y1 > (c->y2+c->ht2)) || (c->y2 > (c->y1+c->ht1))));
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
Utilizes the Manhattan distance to find
the distance between two positions.
*/
double get_distances(Distance *target)
{
   double val = abs(target->p1_x - target->p2_x) + abs(target->p1_y - target->p2_y);
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

