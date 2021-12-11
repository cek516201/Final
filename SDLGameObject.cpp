#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Camera.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams), m_position(pParams->getX(),pParams->getY()), m_velocity(0, 0), m_acceleration(0, 0)
{
  m_width = pParams->getWidth();
  m_height = pParams->getHeight();
  m_textureID = pParams->getTextureID();
  m_currentRow = 0;
  m_currentFrame = 0;
}

void SDLGameObject::draw(SDL_RendererFlip flip)
{
	TheTextureManager::Instance()->drawFrame(m_textureID, (int)(m_position.getX() - TheCamera::Instance()->getCameraMove().getX()), (int)(m_position.getY() - TheCamera::Instance()->getCameraMove().getY()), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), flip);
}

void SDLGameObject::update()
{
  m_velocity += m_acceleration;
  m_position += m_velocity;
}