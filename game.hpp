#pragma once
#include "shot.hpp"

#include "enemy.hpp"

#include "player.hpp"
#include "player.cpp"


#include "map.cpp"



class Game
{
    private:
        int time;
        SDL_Renderer *renderer;
        Player player;
        Enemy enemy;
        Entity background;

        Entity gameStatsBar;

        Shot shot;
        TTF_Font *font;

        // Smoke
        Entity smoke;

        // Zoom Properties
        pair<int, int> screenInitSize;

        // Game Layers
        Matrix<int> layer1; 

        // Collision Trackers
        CollisionStruct *playerEnemyCollision;
        

        // Game Objects
        Matrix<Entity> blocks;

        // Game Textures
        SDL_Texture *blockTexture;
        SDL_Texture *shotTexture;

        // Scrolling
        pair<float, float> scroll;

        bool smokeAnimationAllow;
        Player *attackedPlayer;
        
    public:
        explicit Game();
        void loadTextures();
        void loadWorld();
        void render();
        void animate();
        void collisionManager();
        void eventHandler(SDL_Window *window, SDL_Event &event, int &done);
        
        // Game

        void initGameStatsBar();
        void renderGameStatsBar(SDL_Rect &rect);

        template <typename T>
        void makeSmokeRect(SDL_Rect rect, T *plyr);
        void smokeAnimation();

        inline void allowSmokeAnimation() { smokeAnimationAllow = true; }
        inline void disallowSmokeAnimation() { smokeAnimationAllow = false; }
        inline bool getSmokeAnimationState() { return smokeAnimationAllow; }

        // Font
        inline void setFont(TTF_Font *font) { this->font = font; }
        inline TTF_Font* getFont() { return font; }



        // Player

        inline void setPlayer(const Player &p) { player = p; }
        inline Player* getPlayer() { return &player; };

        inline void setEnemy(const Enemy &e) { enemy = e; }
        inline Enemy* getEnemy() { return &enemy; }

        inline Entity* getSmoke() { return &smoke; }

        inline Entity* getBackground() { return &background; }

        inline void setScrollX(int s) { scroll.first = s; }
        inline int getScrollX() { return scroll.first; }

        inline void setScrollY(int s) { scroll.second = s; }
        inline int getScrollY() { return scroll.second; }

        void playerTextureLoading(int idx, int size, SDL_Surface *surface, Player *entity);

        // Blocks

        inline Matrix<Entity>* getBlocks() { return &blocks; }



        // Zoom
        inline void setScreenHeight(int h) { screenInitSize.first = h; }
        inline int getScreenHeight() { return screenInitSize.first; }
        inline void setScreenWidth(int w) { screenInitSize.second = w; }
        inline int getScreenWidth() { return screenInitSize.second; }

        inline void zoomOut() {
            if (!((getScreenWidth() <= (SCREEN_WIDTH / 1.2)) && (getScreenHeight() <= (SCREEN_HEIGHT / 1.2))))
            {
                setScreenHeight(getScreenHeight() - 1);
                setScreenWidth(getScreenWidth() - 1);
                SDL_RenderSetLogicalSize(this->getRenderer(), getScreenWidth(), getScreenHeight());
            }
        }

        inline void zoomIn() {
            if (!((getScreenWidth() >= (SCREEN_WIDTH * 1.2)) && (getScreenHeight() >= (SCREEN_HEIGHT * 1.2))))
            {
                setScreenHeight(getScreenHeight() + 1);
                setScreenWidth(getScreenWidth() + 1);
                SDL_RenderSetLogicalSize(this->getRenderer(), getScreenWidth(), getScreenHeight());   
            }
        }


        // Shot
        inline Shot* getShot() { return &shot; }
        void shotMovement();
        void matchShotPosition(Player *player);

        // Renderer

        inline void setRenderer(SDL_Renderer *r) { renderer = r; }
        inline SDL_Renderer* getRenderer() { return renderer; }



        template <typename T>
        int mapCollision(T &plyr, Matrix<Entity> &blocks, int row, int col, int, int );
        void enemyPlayerCollision(const Uint8 *state);

        // Textures

        inline void setBlockTexture(SDL_Texture *t) { blockTexture =  t; }
        inline SDL_Texture* getBlockTexture() { return blockTexture; }

        inline void setShotTexture(SDL_Texture *t) { shotTexture = t; }
        inline SDL_Texture* getShotTexture() { return shotTexture; }

        void setConstantTextures(vector<void (Game::*)(SDL_Texture*)> &constantTextures, 
            vector<pair<std::string, std::string> > &messageMap,
            SDL_Surface *surface,
            std::string &filePath);

        void setObjectTextures(Entity *obj, int size, 
                                    std::string &filePath, SDL_Surface *surface,
                                    pair<string, string> &messageMap);


        // Time
        inline int getTime() { return time; }
        inline void setTime(int t) { time = t; }

};

