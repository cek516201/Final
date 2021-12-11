#ifndef _UIManager_H_
#define _UIManager_H_

#include "SDL_ttf.h"
#include <map>
#include <string>

class UIManager;

typedef UIManager TheUIManager;

class UIManager
{
private:
    UIManager() {}
    static UIManager* s_pInstance;

public:
    static UIManager* Instance()
    {
        if (s_pInstance == 0)
            s_pInstance = new UIManager();

        return s_pInstance;
    }

    bool init(int fontSize);
    void draw(const std::string& id, int x, int y, int width, int height, SDL_Renderer* pRenderer);

    void addTexture(const std::string& id, SDL_Texture* pTexture) { m_textureMap[id] = pTexture; }
    void deleteTexture(const std::string& id) { SDL_DestroyTexture(m_textureMap[id]); }
    TTF_Font* getFont() const { return font; }

private:
    TTF_Font* font;

    std::map<std::string, SDL_Texture*> m_textureMap;
};

#endif