#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include "GameObject.h"
#include "Sprite.h"

class Astroid : public GameObject
{
private:
    int hitpoints;
    float speed;
    int power;
    Sprite *explosion;

public:
    Astroid(float x, float y, float w, float h, bool collision, int hitpoints, float speed, int power) : GameObject("images/astroidSpriteSheet.png", 2, 2, x, y, w, h, collision)
    {

        this->hitpoints = hitpoints;
        this->speed = speed;
        this->power = power;
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
    //Combat:
    void reduce_hitpoints(int damage)
    {
        this->set_hitpoints(this->get_hitpoints() - damage);
    }
    // Collision:
    void collide()
    {
    }
};