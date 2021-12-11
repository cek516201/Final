#include <iostream>
#include "Game.h"

const int WINDOW_WIDTH = 960;
const int WINDOW_HEIGHT = 540;
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[])
{
    if (TheGame::Instance()->init("Chapter 1", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, false) == false)
    {
        cout << "game init failure" << SDL_GetError() << endl;

        return 1;
    }

    Uint32 frameStart, frameTime;

    while( TheGame::Instance()->running() )
    {
        frameStart = SDL_GetTicks();

        TheGame::Instance()->handleEvents();
        TheGame::Instance()->update();
        TheGame::Instance()->render();

        frameTime = SDL_GetTicks() - frameStart;
    
        if(frameTime < DELAY_TIME)
        {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }

    TheGame::Instance()->clean();

    return 0;
}