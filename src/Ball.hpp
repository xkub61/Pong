#include "Screen.hpp"
#include "Vector2d.hpp"
#include <cstdlib>
#include <ctime>

class Ball
{
private:
    Screen *display;
    SDL_Texture *texture;
    
    
    void aplyMovement();

public:
    int speed ;
    Vector2d direction;
    SDL_Rect rect;
    void update();
    void render();
    void cleanUp();
    void restart(int lado);
    Ball(Screen *display_ptr);
};

Ball::Ball(Screen *display_ptr)
:display(display_ptr),direction(Vector2d(1,1)),texture(nullptr)
{
    this->speed = 4;
    SDL_Surface *surf = nullptr;
    surf = IMG_Load("assets/ball.png");
    this->rect = this->display->getRectFromSurface(surf);
    this-> rect.h *= 8;
    this-> rect.w *= 8;
    this->rect.x = 200;
    
    this->texture = this->display->CreateTextureFromSurface(surf);
    SDL_FreeSurface(surf);
    srand(time(nullptr));
    this->rect.y = rand() % (this->display->getWindowRect().h - this->rect.h);
    
}


void Ball::aplyMovement(){
    
    if (this->rect.y <= 0)
    {
        this->direction.y *= -1;
    }
    if (this->rect.y >= (this->display->getWindowRect().h - this->rect.h))
    {
        this->direction.y *= -1;
    }
    this->rect.x += this->speed * this->direction.x;
    this->rect.y += this->speed * this->direction.y;
}

void Ball::restart(int lado){
    
    if(lado == 1){
        this->direction.x = -1;
        this->direction.y *= -1;

        this->rect.x = this->display->getWindowRect().w - 200;
        this->rect.y = rand() % (this->display->getWindowRect().h - this->rect.h);
    }
    else{
        this->direction.x = 1;
        this->direction.y *= -1;

        this->rect.x = 200;
        this->rect.y = rand() % (this->display->getWindowRect().h - this->rect.h);
    }

    
}

void Ball::render(){
    this->display->render(this->texture,nullptr,&this->rect);
}

void Ball::update(){
    this->aplyMovement();
}
void Ball::cleanUp()
{
    SDL_DestroyTexture(this->texture);
}