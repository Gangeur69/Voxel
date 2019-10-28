#ifndef GUITEXTBUTTON_H
#define GUITEXTBUTTON_H

#include "GuiButton.h"
#include "../text/Font.h"
#include "../text/Text.h"

#include "../GuiRenderer.h"

using namespace gt::doubovik::gui::text;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace components
      {
        class GuiTextButton : public GuiButton
        {
        private:
          float borderSize;
          Text text;
        public:
          GuiTextButton(const char*, Font*, float, bool, float, float);
          GuiTextButton(const GuiTextButton&);
          GuiTextButton& operator=(const GuiTextButton&);

          virtual void onLeftClick();
          virtual void render(GuiRenderer*, float, float);
        };
      }
    }
  }
}

#endif
