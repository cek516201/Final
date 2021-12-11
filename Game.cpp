#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "UIManager.h"
#include "Camera.h"
#include "CollisionManager.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char *title, int xpos, int ypos, int width, int height, int flags)
{
    if (initSDL(title, xpos, ypos, width, height, flags) == false)
    {
        return false;
    }

    if (loadAssets() == false)
    {
        return false;
    }

    if (initUI(30) == false)
    {
        return false;
    }

    createObjects();

    m_bRunning = true;

    return true;
}

bool Game::initSDL(const char* title, int xpos, int ypos, int width, int height, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return false; // SDL 초기화 실패
    }

    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (m_pWindow == 0)
    {
        return false; // 윈도우 생성 실패
    }
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if (m_pRenderer == 0)
    {
        return false; // 랜더러 생성 실패
    }
}

bool Game::loadAssets()
{
    if (TheTextureManager::Instance()->load("Assets/animate.png", "player", m_pRenderer) == false)
    {
        return false; // 고양이 이미지 로드 실패 
    }

    if (TheTextureManager::Instance()->load("Assets/wall.png", "wall", m_pRenderer) == false)
    {
        return false; // 벽 이미지 로드 실패
    }

    if (TheTextureManager::Instance()->load("Assets/bullet.png", "bullet", m_pRenderer) == false)
    {
        return false; // 총알 이미지 로드 실패
    }

    if (TheTextureManager::Instance()->load("Assets/background.png", "background", m_pRenderer) == false)
    {
        return false; // 배경 이미지 로드 실패
    }

    if (TheTextureManager::Instance()->load("Assets/star.png", "goal", m_pRenderer) == false)
    {
        return false; // 별 이미지 로드 실패
    }
}

bool Game::initUI(int fontSize)
{
    if (TheUIManager::Instance()->init(fontSize) == false)
    {
        return false;
    }

    return true;
}

void Game::createObjects()
{
    int backgroundWidth = 960;
    int backgroundHeight = 3240;
    createTheBackground(0, 0, backgroundWidth, backgroundHeight);

    createThePlayerObject(WINDOW_WIDTH/2, backgroundHeight-100, 64, 41);

    int wallWidth = 40;
    int wallHeight = 40;
    for (int y = 0; y < backgroundHeight/wallHeight; y++)
    {
        for (int x = 0; x < backgroundWidth/wallWidth; x++)
        {
            if (map[y][x] == 1)
            {
                createWallObject(wallWidth*x, wallHeight*y, wallWidth, wallHeight);
            }
            else if (map[y][x] == 2)
            {
                createTheGoalObject(wallWidth*x, wallHeight*y, wallWidth, wallHeight);
            }
        }
    }

    createTheCamera();

    createTheClearTime(0, 0, "clearTime");
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    TheBackground::Instance()->draw();

    ThePlayer::Instance()->draw();

    for (int i = 0; i < m_wallObjects.size(); i++)
    {
        m_wallObjects[i]->draw();
    }

    TheGoal::Instance()->draw();

    for (int i = 0; i < m_bulletObjects.size(); i++)
    {
        m_bulletObjects[i]->draw();
    }

    for (int i = 0; i < m_UIObjects.size(); i++)
    {
        m_UIObjects[i]->draw();
    }

    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    ThePlayer::Instance()->update();

    for(int i = 0 ; i < m_bulletObjects.size() ; i++)
    {
        m_bulletObjects[i]->update();
    }

    TheCamera::Instance()->update();

    for (int i = 0; i < m_UIObjects.size(); i++)
    {
        m_UIObjects[i]->update();
    }
}

void Game::handleEvents() 
{
  TheInputHandler::Instance()->update();
}

void Game::clean() 
{
    TheBackground::Instance()->clean();

    ThePlayer::Instance()->clean();

    for (int i = 0; i < m_wallObjects.size(); i++)
    {
        m_wallObjects[i]->clean();
    }

    TheGoal::Instance()->draw();

    for (int i = 0; i < m_bulletObjects.size(); i++)
    {
        m_bulletObjects[i]->clean();
    }

    for (int i = 0; i < m_UIObjects.size(); i++)
    {
        m_UIObjects[i]->clean();
    }

    TheInputHandler::Instance()->clean();
  
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}