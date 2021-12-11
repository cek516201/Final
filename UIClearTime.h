#ifndef _UIClearTime_H_
#define _UIClearTime_H_

#include "UI.h"

class UIClearTime;

typedef UIClearTime TheUIClearTime;

class UIClearTime : public UI
{
private:
    UIClearTime(const LoaderParams* pParams) : UI(pParams) {}
    static UIClearTime* s_pInstance;

public:
    static UIClearTime* Instance(int x, int y, const string& UIID)
    {
        if (s_pInstance == 0)
            s_pInstance = new UIClearTime(new LoaderParams(x, y, 0, 0, UIID));

        return s_pInstance;
    }

    void draw();
    void update();
    void clean();

private:
    SDL_Surface* surface = 0;
    SDL_Texture* texture = 0;
};

#endif