#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>

#include "../utils/LinkedList.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      extern bool DISPLAY_WINDOW_CLOSED;
      extern int MOUSE_MOVE_X;
      extern int MOUSE_MOVE_Y;
      extern int MOUSE_X;
      extern int MOUSE_Y;
      extern int MOUSE_WHEEL_X;
      extern int MOUSE_WHEEL_Y;

      void initDisplay(const char*, int, int);
      void cleanDisplay();
      void updateDisplay();
      void handleKeys(const SDL_Event&);
      void onKeyPressed(const SDL_Keycode&);
      void onKeyReleased(const SDL_Keycode&);
      bool isPressed(const SDL_Keycode&);
      bool isToggledKey(const SDL_Keycode&);
      bool isToggledMouseButton(unsigned int);
      void grabMouse();
      void clearDisplay(float, float, float, float);
    }
  }
}

#endif
