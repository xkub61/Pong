#include "Screen.hpp"

Screen::Screen(const char* screen_caption,int screen_width, int screen_height)
:caption(screen_caption),width(screen_width),height(screen_height)
{
    window = SDL_CreateWindow(caption,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            width,
                            height,
                            SDL_WINDOW_OPENGL);
    if(window == nullptr){
        erros = SDL_GetError();
    }
    this->setWindowIcon();
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr){
        erros.append("\n");
        erros.append(SDL_GetError());
    }
    this->window_rect.x = 0;
    this->window_rect.y = 0;
    this->window_rect.w = this->width;
    this->window_rect.h = this->height;
}







void Screen::setWindowIcon(){
    SDL_Surface* icon_surf = nullptr;
    icon_surf = IMG_Load("assets/pong.png");

    SDL_SetWindowIcon(this->window,icon_surf);

    SDL_FreeSurface(icon_surf);
    
    return;
}



void Screen::fill( int rval,int gval,int bval,int aval){
    SDL_SetRenderDrawColor(this->renderer,rval,gval,bval,aval);
    return;
}



void Screen::clear(){
    SDL_RenderClear(this->renderer);
    return;
}



void Screen::render(SDL_Texture* texture, SDL_Rect * src_rect, SDL_Rect * dst_rect ){
    SDL_RenderCopy(this->renderer,texture,src_rect,dst_rect);
    return;
}



void Screen::update(){
    SDL_RenderPresent(this->renderer);
    return;
}



SDL_Texture* Screen::LoadTextureFromFile(const char* file_path){
    SDL_Texture *texture = IMG_LoadTexture(this->renderer,file_path);
    return texture;
}



SDL_Texture* Screen::CreateTextureFromSurface(SDL_Surface * surface){

    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer,surface);
    if(texture == nullptr){
        cout << "nullptr texture" << endl;
    }
    return texture;
}



void Screen::getErrors(){
    cout<< erros << endl;
    return;
}



SDL_Rect Screen::getRectFromSurface(SDL_Surface *surf){
    SDL_Rect rect;
    if (surf == nullptr)
    {
        rect.x = 0;
        rect.y = 0;
        rect.w = 1;
        rect.h = 1;
    }
    else{
        rect.x = 0;
        rect.y = 0;
        rect.w = surf->w;
        rect.h = surf -> h;
    }
    return rect;
}


SDL_Rect Screen::getWindowRect(){
    return this->window_rect;
}


void Screen::destroy(){
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}