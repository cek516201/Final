#ifndef _TextureManager_H_
#define _TextureManager_H_

#include "SDL.h"
#include <string>
#include <map>

using namespace std;

class TextureManager;

typedef TextureManager TheTextureManager;

class TextureManager
{
private:
  TextureManager() {}
  static TextureManager* s_pInstance;

public:
  static TextureManager* Instance()
  {
    if(s_pInstance == 0)
      s_pInstance = new TextureManager();

    return s_pInstance;
  }

  bool load(string fileName, string id, SDL_Renderer* pRenderer);
  void drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip);

private:
  map<string, SDL_Texture*> m_textureMap;
};

#endif