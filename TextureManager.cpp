#include "TextureManager.h"
#include "SDL_image.h"

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(string fileName, string id, SDL_Renderer* pRenderer)
{
  SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
  if(pTempSurface == 0)
  {
    return false; // 이미지 로드 실패
  }

  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
  if(pTexture == 0)
  {
    return false; // 텍스쳐 생성 실패
  }
  SDL_FreeSurface(pTempSurface);

  m_textureMap[id] = pTexture;

  return true;
}

void TextureManager::drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
  SDL_Rect srcRect;
  SDL_Rect destRect;

  // 원본상자 설정
  srcRect.x = width * currentFrame; // 시작 x좌표
  srcRect.y = height * currentRow; // 시작 y좌표
  srcRect.w = width; // 너비
  srcRect.h = height; // 높이

  // 대상상자 설정
  destRect.x = x; // 시작 x좌표
  destRect.y = y; // 시작 y좌표
  destRect.w = width; // 너비
  destRect.h = height; // 높이

  SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, NULL, flip);
}