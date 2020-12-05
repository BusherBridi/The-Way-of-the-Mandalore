#include <iostream>
#include "App.h"
#include "SpaceShip.h"
#include "Astroid.h"
#include "ctime"
#include <cmath>

static App *singleton;
int counter = 0;
void razorcrestTimer(int id)
{
    singleton->razorcrest->advance();
    singleton->redraw();
    if (singleton->razorcrest->isDone())
    {
        singleton->razorcrest->reset();
    }
    glutTimerFunc(150, razorcrestTimer, id);
}
void xwingTimer(int id)
{
    for (int i = 0; i < singleton->xwings.size(); i++)
    {
        singleton->xwings[i]->advance();
        singleton->redraw();
        if (singleton->xwings[i]->isDone())
        {
            singleton->xwings[i]->reset();
        }
    }
    glutTimerFunc(150, xwingTimer, id);
}
void xwingFireTimer(int id)
{
    for (int i = 0; i < singleton->xwings.size(); i++)
    {
        srand(time(0));
        if (rand() % 2 == 0)
        {
            singleton->xwings[i]->fire();
        }
    }
    glutTimerFunc(1000, xwingFireTimer, id);
}
void explosionTimer(int id)
{

    singleton->razorcrest->get_explosionSprite()->advance();
    singleton->redraw();
    if (singleton->razorcrest->get_explosionSprite()->isDone())
    {
        singleton->explosionVisible = false;
        // exit(0);
    }
    glutTimerFunc(1000, explosionTimer, id);
}
void astroidTimer(int id)
{
    for (int i = 0; i < singleton->astroids.size(); i++)
    {
        singleton->astroids[i]->advance();
        singleton->redraw();
        if (singleton->astroids[i]->isDone())
        {
            singleton->astroids[i]->reset();
        }
    }
    glutTimerFunc(500, astroidTimer, id);
}
void astroidSpawner(int id)
{
    if (singleton->astroids.size() < 4)
    {
        srand(time(0));
        if (rand() % 3 == 0)
        {
            float yCoord = -0.5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1-(-1))));
            
            singleton->astroids.push_back(new Astroid(1, yCoord, 0.2, 0.2, true, 10, 0.005, 5));
        }
    }
    glutTimerFunc(1000, astroidSpawner, id);
}
void moveAstroids(std::deque<Astroid *> astroids)
{
    for(int i = 0; i < astroids.size(); i++){
        astroids[i]->move_right();
    }
}
void oscillate(SpaceShip *spaceship, int start, int x)
{
    if (start % 2 == 0)
    {
        if (sin(x / 35.0) > 0)
        {
            spaceship->move_up();
        }
        if (sin(x / 35.0) <= 0)
        {

            spaceship->move_down();
        }
    }
    if (start % 2 != 0)
    {
        if (-sin(x / 35.0) > 0)
        {
            spaceship->move_up();
        }
        if (-sin(x / 35.0) <= 0)
        {
            spaceship->move_down();
        }
    }
}
App::App(int argc, char **argv, int width, int height, const char *title) : GlutApp(argc, argv, width, height, title)
{
    background = new TexRect("images/background.png",-2,1,4,2);
    razorcrest = new SpaceShip("images/razocrestFlight.png", 5, 1, 0, 0, 0.6, 0.3, true, 1, 0.01, 5, 0.6, -0.05);
    xwings.push_back(new SpaceShip("images/xwingFlight.png", 1, 6, -1.7, 0.2, 0.6, 0.3, true, 10, 0.005, 2, 0.4, 0));
    xwings.push_back(new SpaceShip("images/xwingFlight.png", 1, 6, -1.7, -0.12, 0.6, 0.3, true, 10, 0.005, 2, 0.4, 0));
    // explosion = new Sprite("explosion.png", 5, 5, -0.8, 0.8, 0.5, 0.5);
    explosionVisible = false;
    singleton = this;
    razorcrestTimer(1);
    xwingTimer(2);
    xwingFireTimer(3);
    astroidTimer(5);
}

void App::draw() const
{
    background->draw(0);
    razorcrest->draw(0.5);
    for (int i = 0; i < xwings.size(); i++)
    {
        xwings[i]->draw(0.5);
    }
    razorcrest->moveProjectile();
    for (int i = 0; i < xwings.size(); i++)
    {
        xwings[i]->moveProjectile();
    }
    if (explosionVisible == true)
    {
        singleton->razorcrest->get_explosionSprite()->draw(0.6);
    }
    for(int i = 0; i < astroids.size(); i++){
        astroids[i]->draw(0.5);
    }
    if(explosionVisible){
        explosionTimer(4);
    }
}
void App::idle()
{
    // if(razorcrest->get_hitpoints() <= 0){
    //     // delete razorcrest;
    //     razorcrest->collide();
    //     explosionVisible = true;
    //     explosionTimer(4);
    //     std::cout<<"GAME OVER\n";
    // }
    for (int i = 0; i < xwings.size(); i++)
    {
        oscillate(xwings[i], i, counter);
        for (int j = 0; j < xwings[i]->projectiles.size(); j++)
        {
            //Razorcrest hit by xwing projectile
            if (razorcrest->contains(xwings[i]->projectiles[j]->getX(), xwings[i]->projectiles[j]->getY()))
            {
                // delete xwings[i]->projectiles[j];
                xwings[i]->projectiles.pop_front();
                razorcrest->collide();
                explosionVisible = true;
                explosionTimer(4);
                razorcrest->reduce_hitpoints(xwings[i]->get_power());
            }
        }
    }
    for (int i = 0; i < astroids.size(); i++){
        if(razorcrest->contains(astroids[i]->getX(), astroids[i]->getY())){
            razorcrest->collide();
                explosionVisible = true;
                explosionTimer(4);
            razorcrest->reduce_hitpoints(astroids[i]->get_power());
            astroids.pop_front();
        }
    }
    astroidSpawner(6);
    moveAstroids(astroids);
    razorcrest->moveProjectile();
    //check bounds on astroids
    for(int i = 0; i < astroids.size(); i++){
        if(astroids[i]->getX() < -1.7){
            // delete astroids[i];
            astroids.pop_front();
        }
    }
    glutPostRedisplay();
    counter++;
}
void App::keyDown(unsigned char key, float x, float y)
{
    if (key == 27)
    {
        exit(0);
    }
    if (key == 'd')
    {
        if (razorcrest->getX() < 1)
        {
            razorcrest->move_left();
        }
    }
    if (key == 'a')
    {
        if (razorcrest->getX() + razorcrest->getW() > -1)
        {
            // std::cout << razorcrest->getX() << std::endl;
            razorcrest->move_right();
        }
    }
    if (key == 'w')
    {
        if (razorcrest->getY() < 1)
        {
            razorcrest->move_up();
        }
    }
    if (key == 's')
    {
        if (razorcrest->getY() - razorcrest->getH() > -1)
        {

            razorcrest->move_down();
        }
    }
}
void App::keyUp(unsigned char key, float x, float y)
{
    if (key == ' ')
    {
        razorcrest->fire();
    }
}

App::~App()
{
    delete razorcrest;
    for (int i = 0; i < xwings.size(); i++)
    {
        delete xwings[i];
    }
    std::cout << "Exiting..." << std::endl;
}
