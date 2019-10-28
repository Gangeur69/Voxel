#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include "../GuiRenderer.h"
#include "../GuiComponent.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace components
      {
        class GuiButton : public GuiComponent
        {
        public:
          GuiButton();
          GuiButton(const GuiButton&);
          GuiButton& operator=(const GuiButton&);

          virtual void onLeftClick();
          virtual void render(GuiRenderer*, float, float);
        };
      }
    }
  }
}

#endif
