#ifndef Game_h
#define Game_h

#include <vector>
#include "GlutApp.h"
#include "Rect.h"
#include "Circle.h"
#include "TexRect.h"
#include "Sprite.h"
#include "GameObject.h"
#include "SpaceShip.h"
#include "Astroid.h"
#include "vector"
#include "deque"
class Game : public GlutApp
{
    TexRect * background;
    std::vector<GameObject *> objects;
    SpaceShip *razorcrest;
    std::vector<SpaceShip *> xwings;
    std::deque<Astroid *> astroids;
    // Sprite *explosion;
    bool explosionVisible = false;
    bool gameState = true;
    

public:
    Game(int argc, char **argv, int width, int height, const char *title);

    void draw() const;

    void keyDown(unsigned char key, float x, float y);
    void keyUp(unsigned char key, float x, float y);

    void idle();

    friend void razorcrestTimer(int id);
    friend void xwingTimer(int id);
    friend void xwingFireTimer(int id);
    friend void oscillate(SpaceShip *spaceship, int start, int x);
    friend void explosionTimer(int id);
    friend void astroidTimer(int id);
    friend void astroidSpawner(int id);
    friend void moveAstroids(std::deque<Astroid *> astroids);
    bool getGameState(){
        return gameState;
    }
    void setGameState(bool value){
        gameState = value;
    }
    ~Game();
};

#endif
