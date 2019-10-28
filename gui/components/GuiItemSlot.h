#ifndef GUIITEMSLOT_H
#define GUIITEMSLOT_H

#include "../GuiComponent.h"
#include "../GuiRenderer.h"
#include "GuiItemHolder.h"
#include "../../items/ItemStack.h"
#include "../text/DynamicText.h"
#include "../text/Font.h"

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
        class GuiItemSlot : public GuiComponent
        {
        private:
          GuiItemHolder* itemHolder;
          ItemStack* itemStack;
          Font* font;

          DynamicText itemName;
          DynamicText itemAmount;

          void updateText();
          void swapItemStacks();
        public:
          GuiItemSlot(GuiItemHolder*, ItemStack*, Font*);
          GuiItemSlot(const GuiItemSlot&);
          GuiItemSlot& operator=(const GuiItemSlot&);

          virtual void onLeftClick();
          virtual void render(GuiRenderer*, float, float);
        };
      }
    }
  }
}

#endif
