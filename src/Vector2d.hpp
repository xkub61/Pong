#pragma once

#include<iostream>

typedef struct Vector2d
{
    int x;
    int y;
    Vector2d(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
}Vector2d;

typedef struct VectorF2d
{
    float x;
    float y;
    VectorF2d(float x_, float y_)
    {
        this->x = x_;
        this->y = y_;
    }

    Vector2d toVector2d(){
        return Vector2d(int(this->x), int (this->y));
    }
}VectorF2d;

typedef struct VectorD2d
{
    double x;
    double y;
    VectorD2d(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    Vector2d toVector2d(){
        return Vector2d(int(this->x), int (this->y));
    }
}VectorD2d;