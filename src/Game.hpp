#include "SDL2/SDL_ttf.h"
#include "Screen.hpp"
#include "Player.hpp"
#include "Ball.hpp"


class Game
{
private:
    Screen *display;
    Player player1;
    Player player2;
    Ball ball;
    TTF_Font * font1;
    TTF_Font * font2;
    int player1points;
    int player2points;
    bool play;
    double ballAceleration;
    

    void checkHorizontalCollision();
    void checkForPoint();
    void checkPlayersInput();
    void drawScore();
    void drawMenu();
    void drawPlayerSelection();


public:
    Game(Screen * display_ptr);

    
    void run();
    void cleanUp();
};

Game::Game(Screen * display_ptr)
:display(display_ptr),player1(Player(display_ptr)),player2(Player(display_ptr)),ball(Ball(display_ptr))
{
    this->ballAceleration = 0;

    this->player1.rect.x = this->display->getWindowRect().w - this->player1.rect.w - 30;
    this->player2.rect.x = 30;
    
    this->play = false;
    this->player1points = 0;
    this->player2points = 0;

    this->font1 = TTF_OpenFont("assets/pixellari.ttf",256);
    this->font2 = TTF_OpenFont("assets/minecraft.ttf",16);
    
}




void Game::drawMenu(){
    SDL_Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

    SDL_Surface *surf = TTF_RenderText_Solid(this->font1,"PONG",color);
    SDL_Rect Title_rect = this->display->getRectFromSurface(surf);
    Title_rect.x = (this->display->getWindowRect().w - Title_rect.w)/2;
    Title_rect.y = 100;
    SDL_Texture * Title_text = this->display->CreateTextureFromSurface(surf);
    SDL_FreeSurface(surf);
    this->display->render(Title_text,nullptr,&Title_rect);
    

    surf = TTF_RenderText_Solid(this->font2,"Press ENTER to start",color);
    SDL_Rect message_rect = this->display->getRectFromSurface(surf);
    message_rect.x =(this->display->getWindowRect().w - message_rect.w)/2;
    message_rect.y = Title_rect.y + Title_rect.h + 70;
    SDL_Texture * message_tex = this->display->CreateTextureFromSurface(surf);
    SDL_FreeSurface(surf);
    this->display->render(message_tex,nullptr,&message_rect);

    const uint8_t *keys = SDL_GetKeyboardState(nullptr);
    if(keys[SDL_SCANCODE_KP_ENTER] || keys[SDL_SCANCODE_RETURN]){
        SDL_DestroyTexture(Title_text);
        SDL_DestroyTexture(message_tex);
        this->play = true;
    }


}



void Game::drawScore(){
    
    SDL_Color color = {255,255,255,255};


    SDL_Surface *surf = TTF_RenderText_Solid(this->font1,"SCORE",color);
    SDL_Rect Score_rect = this->display->getRectFromSurface(surf);
    Score_rect.h = Score_rect.h/4;
    Score_rect.w = Score_rect.w/4;
    Score_rect.x = (this->display->getWindowRect().w - Score_rect.w)/2;
    Score_rect.y = 10;
    SDL_Texture * Score_text = this->display->CreateTextureFromSurface(surf);
    SDL_FreeSurface(surf);
    this->display->render(Score_text,nullptr,&Score_rect);


    surf = TTF_RenderText_Solid(this->font2,"l",color);
    SDL_Rect bar_rect = this->display->getRectFromSurface(surf);
    bar_rect.x = (this->display->getWindowRect().w - bar_rect.w)/2;
    bar_rect.y = Score_rect.y + Score_rect.h + 5;
    bar_rect.h *= 5;
    bar_rect.w *= 3; 
    SDL_Texture * bar_text = this->display->CreateTextureFromSurface(surf);
    SDL_FreeSurface(surf);
    this->display->render(bar_text,nullptr,&bar_rect);

    
    string player_2_points = to_string(this->player2points);
    surf = TTF_RenderText_Solid(this->font2,player_2_points.c_str(),color);
    SDL_Rect p2p_rect = this->display->getRectFromSurface(surf);
    p2p_rect.w *= 4;
    p2p_rect.h *= 4;
    p2p_rect.x =  bar_rect.x - 50 - (p2p_rect.w/2);
    p2p_rect.y = Score_rect.y + Score_rect.h + 15;
    SDL_Texture * p2p_text = this->display->CreateTextureFromSurface(surf);
    SDL_FreeSurface(surf);
    this->display->render(p2p_text,nullptr,&p2p_rect);


    string player_1_points = to_string(this->player1points);
    surf = TTF_RenderText_Solid(this->font2,player_1_points.c_str(),color);
    SDL_Rect p1p_rect = this->display->getRectFromSurface(surf);
    p1p_rect.w *= 4;
    p1p_rect.h *= 4;
    p1p_rect.x =  bar_rect.x + bar_rect.w + 50 - (p1p_rect.w/2);
    p1p_rect.y = Score_rect.y + Score_rect.h + 15;
    SDL_Texture * p1p_text = this->display->CreateTextureFromSurface(surf);
    SDL_FreeSurface(surf);
    this->display->render(p1p_text,nullptr,&p1p_rect);


    SDL_DestroyTexture(Score_text);
    SDL_DestroyTexture(bar_text);
    SDL_DestroyTexture(p2p_text);
    SDL_DestroyTexture(p1p_text);

}



void Game::checkPlayersInput(){

    const uint8_t *keys =  SDL_GetKeyboardState(nullptr);
    if (keys[SDL_SCANCODE_UP] )//player 1
    {
        if(this->player1.rect.y > 0){
            this->player1.rect.y -= this->player1.speed;
        }
    }
    if(keys[SDL_SCANCODE_DOWN] )
    {
        if((this->player1.rect.y + this->player1.rect.h) < this->display->getWindowRect().h){
            this->player1.rect.y += this->player1.speed;
        }
    }
    
    if (keys[SDL_SCANCODE_W] )//player 2
    {
        if(this->player2.rect.y > 0){
            this->player2.rect.y -= this->player2.speed;
        }
    }
    if(keys[SDL_SCANCODE_S] )
    {
        if((this->player2.rect.y + this->player2.rect.h) < this->display->getWindowRect().h){
            this->player2.rect.y += this->player2.speed;
        }
    }
}



void Game::checkForPoint(){

    if(this->ball.direction.x < 0){
         
        if(this->ball.rect.x <= 0){
            this->player1points++;
            this->ball.restart(1);
            this->ball.speed = 4;
            this->ballAceleration = 0;
        } 
        
    }
    else{
        if((this->ball.rect.x + this->ball.rect.w) >= this->display->getWindowRect().w){
            this->player2points++;
            this->ball.restart(2);
            this->ball.speed = 4;
            this->ballAceleration = 0;
        } 
    }


    
}



void Game::checkHorizontalCollision(){

    if (this->ball.direction.x > 0){

        SDL_Rect rect_a = this->player1.rect;
        SDL_Rect rect_b = this->ball.rect;
        if(SDL_HasIntersection(&rect_a,&rect_b))
        {
            this->ball.direction.x *= -1;
            this->ballAceleration += 0.1;
        }
    }
    else{
        SDL_Rect rect_a = this->player2.rect;
        SDL_Rect rect_b = this->ball.rect;
        if(SDL_HasIntersection(&rect_a,&rect_b))
        {
            this->ball.direction.x *= -1;
            this->ballAceleration += 0.1;
        }
    }
    this->ball.speed += int(this->ballAceleration);
}



void Game::cleanUp(){
    
    TTF_CloseFont(this->font1);
    TTF_CloseFont(this->font2);
    this->player1.cleanUp();
    this->player2.cleanUp();
    this->ball.cleanUp();
}



void Game::run(){
    if(this->play){
        this->checkHorizontalCollision();
        this->checkPlayersInput();
        this->ball.update();
        this->checkForPoint();

        this->player1.render();
        this->player2.render();
        this->ball.render();
        this->drawScore();
    }
    else{
        this->drawMenu();
    }
    
}