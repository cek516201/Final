#ifndef _UI_H_
#define _UI_H_

#include "SDL_ttf.h"
#include "GameObject.h"

class UI : public GameObject
{
public:
	UI(const LoaderParams* pParams);
	virtual ~UI() {}

	void draw();
	void update() {}
	void clean() {}

	Vector2D getPosition() { return m_position; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

protected:
	SDL_Color color = { 255, 0, 0, SDL_ALPHA_OPAQUE };

	Vector2D m_position; // :  m_position(pParams->getX(),pParams->getY())
	int m_width;
	int m_height;
	string m_textureID;
};

#endif