#include "UIClearTime.h"
#include "UIManager.h"
#include "Game.h"

UIClearTime* UIClearTime::s_pInstance = 0;

void UIClearTime::draw()
{
	UI::draw();
}

void UIClearTime::update()
{
    surface = TTF_RenderText_Blended(TheUIManager::Instance()->getFont(), ("clear time : " + std::to_string(SDL_GetTicks()/60000) + ":" + std::to_string(SDL_GetTicks()/1000%60)).c_str(), color);
    texture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), surface);
    SDL_FreeSurface(surface);
    
    m_width = surface->w;
    m_height = surface->h;
    
    TheUIManager::Instance()->addTexture(m_textureID, texture);
}

void UIClearTime::clean()
{
    TheUIManager::Instance()->deleteTexture(m_textureID);
    TTF_CloseFont(TheUIManager::Instance()->getFont());
}