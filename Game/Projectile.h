#pragma once
#include <iostream>
#include "GameObject.h"

class Projectile : public GameObject
{
private:
    float speed;
    int damage;

public:
    Projectile(const char *filename, int rows, int cols, float x, float y, float w, float h, bool collision, float speed, int damage) : GameObject(filename, rows, cols, x, y, w, h, collision)
    {
        this->speed = speed;
        this->damage = damage;
    }

    //Getters:
    float get_speed()
    {
        return this->speed;
    }
    int get_damage()
    {
        return this->damage;
    }

    //Setters:
    void set_speed(float value){
        this->speed=value;
    }
    void set_damage(float value){
        this->damage=value;
    }

    //Movement:
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


};