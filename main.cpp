#include <iostream>
#include <vector>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_mixer.h>
#include <SDL2\SDL_ttf.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

/*
Objective 

Try to make a shooter similar
to the one at Children's Lighthouse

*/


/*
A simple Entity Class
*/
class Entity 
{
    private:
      /* data */
      float x, y;
      float dx, dy;
      int frame;
      std::vector<SDL_Texture*> sprites;
    public:
        Entity(float x, float y, int size);
        inline float get_x() { return x; }
        inline void set_x(float v) { x = v; }
        inline float get_y() { return y; }
        inline void set_y(float v) { y = v; }
        inline float get_dx() { return dx; }
        inline void set_dx(float v) { dx = v; }
        inline float get_dy() { return dy; }
        inline void set_dy(float v) { dy = v; }

        inline void setSprite(int idx, SDL_Texture* sprite) { sprites.at(idx) = sprite; }
        inline SDL_Texture* getSprite(int idx) { return sprites.at(idx); }

        inline void setFrame(int f) { frame = f; }
        inline int getFrame() { return frame; }
};

Entity::Entity(float x, float y, int size)
{
    this->set_x(x);
    this->set_y(y);
    sprites = std::vector<SDL_Texture*>(size);
    this->setFrame(0);
};




class Game
{
    private:
        SDL_Renderer *renderer;
    public:
        inline void set_renderer(SDL_Renderer *r) { renderer = r; }
        inline SDL_Renderer* get_renderer() { return renderer; }
};

int main(int argc, char **argv)
{
    Game game;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    window = SDL_CreateWindow(
        "Shooter",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    game.set_renderer(renderer);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);


    int done = 0;

    Entity mov(0, 0, 1);
    mov.set_x(0);
    mov.set_y(0);

    SDL_Event event;
    while (!done)
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
                {
                    done = 1;
                }
                break;
                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE: {
                            done = 1;
                        }
                        break;
                        case SDLK_UP: {
                            mov.set_y(mov.get_y() - 1);
                        }
                        break;
                        case SDLK_DOWN: {
                            mov.set_y(mov.get_y() + 1);
                        }
                        break;
                        case SDLK_LEFT: {
                            mov.set_x(mov.get_x() - 1);
                        }
                        break;
                        case SDLK_RIGHT: {
                            mov.set_x(mov.get_x() + 1);
                        }
                        break;
                    }
                }
            }
        }
        std::cout << mov.get_x() << " " << mov.get_y() << std::endl;
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(game.get_renderer());
    return 0;
}