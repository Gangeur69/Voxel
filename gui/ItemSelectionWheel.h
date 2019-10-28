#ifndef ITEMSELECTIONWHEEL_H
#define ITEMSELECTIONWHEEL_H

#include "GuiComponent.h"
#include "components/GuiItemDisplay.h"
#include "../graphics/Texture.h"
#include "../items/Inventory.h"
#include "text/Font.h"

using namespace gt::doubovik::graphics;
using namespace gt::doubovik::items;
using namespace gt::doubovik::gui::components;
using namespace gt::doubovik::gui::text;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class ItemSelectionWheel : public GuiComponent
      {
      private:
        int selectedItemStack;
        int maxItemStacks;
        Texture* texture;
        Inventory* inventory;

        GuiItemDisplay** itemDisplays;
        void getTargetPosition(int, float*, float*) const;
        void checkSelection();
        void setTransitions();
        void setInitialPositions();
      public:
        ItemSelectionWheel(int, Texture*, Inventory*, Font*);
        ItemSelectionWheel(const ItemSelectionWheel&);
        ItemSelectionWheel& operator=(const ItemSelectionWheel&);
        virtual ~ItemSelectionWheel();

        virtual void render(GuiRenderer*, float, float);
        virtual void update(float timePassed);

        void next();
        void previous();

        ItemStack* getSelectedItem() const;
      };
    }
  }
}

#endif
