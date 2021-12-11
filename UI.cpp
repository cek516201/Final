#include "UI.h"
#include "Game.h"
#include "UIManager.h"

UI::UI(const LoaderParams* pParams) : GameObject(pParams), m_position(pParams->getX(), pParams->getY())
{
    m_textureID = pParams->getTextureID();
}

void UI::draw()
{
    TheUIManager::Instance()->draw(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, TheGame::Instance()->getRenderer());
}