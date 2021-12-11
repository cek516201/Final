// 조작법
// 좌우 방향키 : 지면에서 이동, 점프 시 방향 결정
// 스페이스 바 : 눌렀다 뗀 정도에 따라 점프력 결정
// 마우스 왼쪽 클릭 : 마우스 위치로 총알 발사(플레이 중 필수적이진 않음)

// 추가한 파일 설명
// Background.cpp, h : 배경
// Bullet.cpp, h : 총알
// Camera.cpp, h : 화면스크롤 구현을 위한 카메라 개념
// CollisionManager.cpp, h : 충돌 여부를 반환해주는 객체
// Goal.cpp, h : 클리어를 위한 최종목표지점
// Player.cpp, h : 플레이어
// UI.cpp, h : UI
// UIClearTime.cpp, h : 클리어타임
// UIManager. cpp, h : 폰트 초기화와 UI를 그려주는 객체
// Wall.cpp, h : 벽

// 수정한 코드 설명
// SDLGameObject. cpp : 화면스크롤 구현을 위해 draw() 수정

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