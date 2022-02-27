#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Screen.hpp"
#include "Game.hpp"

#define FPS 60
using namespace std;

int main(int argc,char* argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        
        cout << "Erro ao inicializar o SDL . ERRO : "<< SDL_GetError() << endl;
        return 1;
    }
    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
        cout << "Erro ao inicializar o SDL IMG . ERRO : "<< IMG_GetError() << endl;
        SDL_Quit();
        return 1;
    }
    if(TTF_Init() == -1){
        cout << "Erro ao inicializar o SDL TTF . ERRO : "<< TTF_GetError() << endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    
    
    Screen display("Pong", 1000 , 600);

    
    Game game(&display);

    
    
    //escrita e calculo da duração do frame
    string fps_s = "FPS  0";
    int fps_counter = 0;
    uint32_t dt = SDL_GetTicks();

    SDL_Event events;
    bool game_run = true;

    while (game_run)
    {
        //para calculo do tempo de frame
        dt = SDL_GetTicks();
        uint32_t dt2 = dt;
        
        display.fill(57, 150, 73,255);
        display.clear();
        
        
        while(SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
            {
                game_run = false;
            }
        }

        
        game.run();

        
        display.update();



        //calculo do tempo do frame
        dt = SDL_GetTicks() - dt;
        if(dt < (1000/FPS)){
            SDL_Delay((1000/FPS) - dt);
        }
        
        //calculo para a escrita do fps
        dt2 = SDL_GetTicks() - dt2;
        int fps = 1000/dt2;
        
        fps_counter += 1;
        if (fps_counter >= 30)//escreve o valor do fps a cada 30 frames
        {
            fps_counter = 0;
            fps_s = "FPS  ";
            fps_s += to_string(fps);
            cout << fps_s << endl;
        }

    }
    
    game.cleanUp();
    display.destroy();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}