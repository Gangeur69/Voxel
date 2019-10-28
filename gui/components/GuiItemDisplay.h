#ifndef GUIITEMDISPLAY_H
#define GUIITEMDISPLAY_H

#include "../GuiComponent.h"
#include "../../items/ItemStack.h"

#include "../text/Font.h"
#include "../text/DynamicText.h"

using namespace gt::doubovik::items;
using namespace gt::doubovik::gui::text;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace components
      {
        class GuiItemDisplay : public GuiComponent
        {
        private:
          ItemStack* itemStack;

          DynamicText itemName;
          DynamicText itemAmount;

          void updateText();
        public:
          GuiItemDisplay(ItemStack*, Font* font);
          GuiItemDisplay(const GuiItemDisplay&);
          GuiItemDisplay& operator=(const GuiItemDisplay&);

          virtual void render(GuiRenderer*, float, float);
        };
      }
    }
  }
}

#endif
