#ifndef GUIICONBUTTON_H
#define GUIICONBUTTON_H

#include "GuiButton.h"
#include "../GuiRenderer.h"

#include "../../graphics/Texture.h"

using namespace gt::doubovik::graphics;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace components
      {
        class GuiIconButton : public GuiButton
        {
        private:
          Texture* texture;
          bool* isVisible;
        public:
          GuiIconButton(Texture*, bool*, float, float);
          GuiIconButton(const GuiIconButton&);
          GuiIconButton& operator=(const GuiIconButton&);

          virtual void onLeftClick();
          virtual void render(GuiRenderer*, float, float);
        };
      }
    }
  }
}

#endif
