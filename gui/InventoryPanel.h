#ifndef INVENTORYPANEL_H
#define INVENTORYPANEL_H

#include "Panel.h"
#include "../items/Inventory.h"
#include "../items/ItemStack.h"
#include "text/Font.h"
#include "text/Text.h"
#include "components/GuiItemHolder.h"
#include "components/GuiItemSlot.h"
#include "../utils/String.h"

using namespace gt::doubovik::utils;
using namespace gt::doubovik::items;
using namespace gt::doubovik::gui::components;
using namespace gt::doubovik::gui::text;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class InventoryPanel : public Panel
      {
      private:
        GuiItemHolder* holder;
        Inventory* inventory;
        Font* font;

        Text name;
        GuiItemSlot** slots;

        void generateSlots();
      public:
        InventoryPanel(GuiItemHolder*, Inventory*, Font*);
        InventoryPanel(const InventoryPanel&);
        InventoryPanel& operator=(const InventoryPanel&);
        virtual ~InventoryPanel();
      };
    }
  }
}

#endif
