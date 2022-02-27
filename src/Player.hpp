#include "Screen.hpp"

class Player
{
private:
    Screen * display;
    SDL_Texture * texture;
    
    
public:

    const int speed = 15;
    SDL_Rect rect;
    Player(Screen * display_ptr);
    void update();
    void render();
    void cleanUp();
};

Player::Player(Screen * display_ptr)
:display(display_ptr),texture(nullptr)
{
    SDL_Surface *surf = nullptr;
    surf = IMG_Load("assets/pong_bar.png");
    this->rect = this->display->getRectFromSurface(surf);
    this-> rect.h *= 8;
    this-> rect.w *= 8;
    this->rect.x = 0;
    this->rect.y = 0;
    
    this->texture = this->display->CreateTextureFromSurface(surf);
    SDL_FreeSurface(surf);

}




void Player::render(){
    this->display->render(this->texture,nullptr,&this->rect);
}

void Player::cleanUp(){
    SDL_DestroyTexture(this->texture);
}