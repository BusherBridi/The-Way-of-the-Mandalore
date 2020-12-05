#pragma once
#include <iostream>
#include "Sprite.h"

class GameObject : public Sprite
{
private:
    const char *filename;
    int rows;
    int cols;
    float x;
    float y;
    float w;
    float h;
    bool collision;

public:
    GameObject(const char *filename, int rows, int cols, float x, float y, float w, float h, bool collision) : Sprite(filename, rows, cols, x, y, w, h)
    {
        this->filename = filename;
        this->rows = rows;
        this->cols = cols;
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->collision = collision;
    }
    //Getters:
    float get_x()
    {
        return this->x;
    }
    float get_y()
    {
        return this->y;
    }
    float get_w()
    {
        return this->w;
    }
    float get_h()
    {
        return this->h;
    }
    bool iscollision()
    {
        return this->collision;
    }

    //Setters:
    void set_collision(bool value)
    {
        this->collision = value;
    }
    // Collision:
    virtual void collide() = 0;
    //Movement:
    virtual void move_up() = 0;
    virtual void move_down() = 0;
    virtual void move_right() = 0;
    virtual void move_left() = 0;

    virtual ~GameObject() = default;
};