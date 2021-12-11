#include "UIManager.h"

UIManager* UIManager::s_pInstance = 0;

bool UIManager::init(int fontSize)
{
    if (TTF_Init() < 0)
    {
        return false;
    }

    font = TTF_OpenFont("C:\\Windows\\Fonts\\GULIM.TTC", fontSize);
    if (font == NULL)
    {
        return false;
    }
}

void UIManager::draw(const std::string& id, int x, int y, int width, int height, SDL_Renderer* pRenderer)
{
    SDL_Rect r = { x, y, width, height };

    SDL_RenderCopy(pRenderer, m_textureMap[id], NULL, &r);
}