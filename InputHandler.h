#ifndef _InputHandler_H_
#define _InputHandler_H_

#include "SDL.h"
#include "vector"
#include "Vector2D.h"

class InputHandler;

typedef InputHandler TheInputHandler;

enum mouse_buttons
{
  LEFT = 0,
  MIDDLE = 1,
  RIGHT = 2
};

class InputHandler
{
private:
  InputHandler();
  static InputHandler* s_pInstance;
  
public:
  static InputHandler* Instance()
  {
    if(s_pInstance == 0)
      s_pInstance = new InputHandler();

    return s_pInstance;
  }

  bool isKeyDown(SDL_Scancode key);
  void update();
  void onKeyDown();
  void onKeyUp();
  void onMouseMove(SDL_Event event);
  void onMouseButtonDown(SDL_Event event);
  void onMouseButtonUp(SDL_Event event);
  void clean() {}

  bool getMouseButtonState(int buttonNumber) const { return m_mouseButtonStates[buttonNumber]; }
  Vector2D* getMousePosition() const { return m_mousePosition; }

private:
  const Uint8* m_keystates;

  std::vector<bool> m_mouseButtonStates;
  Vector2D* m_mousePosition;
};

#endif