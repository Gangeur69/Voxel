#ifndef GUIITEMHOLDER_H
#define GUIITEMHOLDER_H

#include "../GuiComponent.h"
#include "../../items/ItemStack.h"
#include "../../items/Item.h"
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
        class GuiItemHolder : public GuiComponent
        {
        private:
          ItemStack* itemStack;
          Font* font;

          DynamicText itemName;
          DynamicText itemAmount;

          void updateText();
        public:
          GuiItemHolder(ItemStack*, Font*);
          GuiItemHolder(const GuiItemHolder&);
          GuiItemHolder& operator=(const GuiItemHolder&);

          void setItem(int, Item*);
          Item* getItem() const;
          int getItemAmount() const;

          virtual void render(GuiRenderer*, float, float);
          virtual void updateMouseData(bool, float, float, float, float);
        };
      }
    }
  }
}

#endif
