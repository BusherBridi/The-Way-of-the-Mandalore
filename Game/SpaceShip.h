#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include "GameObject.h"
#include "Sprite.h"
class SpaceShip : public GameObject
{
private:
    int hitpoints;
    float speed;
    int power;
    float gun_x;
    float gun_y;
    Sprite *explosion;

public:
    std::deque<Sprite *> projectiles;
    SpaceShip(const char *filename, int rows, int cols, float x, float y, float w, float h, bool collision, int hitpoints, float speed, int power, float gun_x, float gun_y) : GameObject(filename, rows, cols, x, y, w, h, collision)
    {
        this->hitpoints = hitpoints;
        this->speed = speed;
        this->power = power;
        this->gun_x = gun_x;
        this->gun_y = gun_y;
    }

    //Getters:
    int get_hitpoints()
    {
        return this->hitpoints;
    }
    float get_speed()
    {
        return this->speed;
    }
    int get_power()
    {
        return this->power;
    }
    float get_gunx()
    {
        return this->gun_x;
    }
    float get_guny()
    {
        return this->gun_y;
    }

    Sprite *get_explosionSprite()
    {
        return this->explosion;
    }
    //Setters
    void set_hitpoints(int value)
    {
        this->hitpoints = value;
    }
    void set_speed(float value)
    {
        this->speed = value;
    }
    void set_power(int value)
    {
        this->power = value;
    }
    void set_gunx(float value)
    {
        this->gun_x = value;
    }
    void set_guny(float value)
    {
        this->gun_y = value;
    }

    //movment:
    void move_up()
    {
        this->setY(this->getY() + this->get_speed());
    }
    void move_down()
    {
        this->setY(this->getY() - this->get_speed());
    }
    void move_right()
    {
        this->setX(this->getX() - this->get_speed());
    }
    void move_left()
    {

        this->setX(this->getX() + this->get_speed());
    }

    // combat:
    void fire()
    {
        this->projectiles.push_back(new Sprite("images/laserTravel.png", 7, 2, this->getX() + this->get_gunx(), this->getY() + this->get_guny(), 0.1, 0.2));
    }
    void moveProjectile()
    {
        for (int i = 0; i < this->projectiles.size(); i++)
        {

            this->projectiles[i]->setX(this->projectiles[i]->getX() + 0.01);
            this->projectiles[i]->draw(0.9);
            this->projectiles[i]->advance();
            if (this->projectiles[i]->isDone())
            {
                this->projectiles[i]->reset();
            }
            // std::cout<<"moving projectile: "<<i<<std::endl;
            // std::cout<<"position of projectile: " << i <<" ="<<this->projectiles[i]->getX();

            if (this->projectiles[i]->getX() > 1.5)
            {
                // delete this->projectiles[i];
                this->projectiles.pop_front();
                std::cout << "Deleting beam\n";
                std::cout << "size: " << this->projectiles.size();
            }
        }
    }
    void reduce_hitpoints(int damage){
        this->set_hitpoints(this->get_hitpoints()-damage);
    }
    // Collision:
    void collide()
    {
        float explosionX = this->getX() + this->get_w() / 2;
        float explosionY = this->getY() + this->get_h() / 2;
        explosion = new Sprite("images/explosion.png", 5, 5, explosionX, explosionY, 0.5, 0.5);
        std::cout << "Collision detected, coords: "<<explosionX<<", "<<explosionY;
    }
};