#include "ItemSelectionWheel.h"
#include <cmath>

#include "transitions/GuiTranslationTransition.h"

using namespace gt::doubovik::gui::transitions;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      ItemSelectionWheel::ItemSelectionWheel(int maxItemStacks, Texture* texture, Inventory* inventory, Font* font) : GuiComponent()
      {
        this->maxItemStacks = maxItemStacks;
        this->texture = texture;
        this->inventory = inventory;
        width = 1.0;
        height = 0.5;
        x = -(width/2.0);
        y = 1.0 - height;

        selectedItemStack = 0;

        itemDisplays = new GuiItemDisplay*[maxItemStacks];
        for(int i=0;i<maxItemStacks;i++)
        {
          *(itemDisplays + i) = new GuiItemDisplay(inventory->getItemStack(i), font);
          (*(itemDisplays + i))->x = 0.0;
          (*(itemDisplays + i))->y = y + height;
        }
        setInitialPositions();
      }

      ItemSelectionWheel::ItemSelectionWheel(const ItemSelectionWheel& itemWheel) : GuiComponent(itemWheel)
      {

      }

      ItemSelectionWheel& ItemSelectionWheel::operator=(const ItemSelectionWheel& itemWheel)
      {
        GuiComponent::operator=(itemWheel);
        return *this;
      }

      ItemSelectionWheel::~ItemSelectionWheel()
      {
        for(int i=0;i<maxItemStacks;i++)
        {
          delete *(itemDisplays + i);
        }
        delete[] itemDisplays;
      }

      void ItemSelectionWheel::getTargetPosition(int i, float* tx, float* ty) const
      {
        float angle = 90.0 - (65.0/2.0)*i;
        angle = (M_PI/180.0)*angle;
        *tx = (width/2.0) + height*cos(angle);
        *ty = height - height*sin(angle);
      }

      void ItemSelectionWheel::setInitialPositions()
      {
        for(int i=-3;i<=3;i++)
        {
          int index = selectedItemStack + i;
          if(index < 0)
          {
            index = maxItemStacks + index;
          }
          else if(index >= maxItemStacks)
          {
            index = index - maxItemStacks;
          }

          float tx;
          float ty;
          getTargetPosition(i, &tx, &ty);
          GuiItemDisplay* itemDisplay = *(itemDisplays + index);
          itemDisplay->x = tx - (itemDisplay->width/2.0);
          itemDisplay->y = ty;
        }
      }

      void ItemSelectionWheel::render(GuiRenderer* renderer, float parentx, float parenty)
      {
        GuiComponent::render(renderer, parentx, parenty);
        renderer->renderQuad(texture, parentx + x, parenty + y, width, height, Vector3(1.0, 1.0, 1.0));

        for(int i=-3;i<=3;i++)
        {
          int index = selectedItemStack + i;
          if(index < 0)
          {
            index = maxItemStacks + index;
          }
          else if(index >= maxItemStacks)
          {
            index = index - maxItemStacks;
          }

          GuiItemDisplay* toRender = *(itemDisplays + index);
          toRender->render(renderer, parentx + x, parenty + y);
        }
      }

      void ItemSelectionWheel::update(float timePassed)
      {
        GuiComponent::update(timePassed);
        for(int i=0;i<maxItemStacks;i++)
        {
          (*(itemDisplays + i))->update(timePassed);
        }
      }

      void ItemSelectionWheel::checkSelection()
      {
        if(selectedItemStack >= maxItemStacks)
        {
          selectedItemStack = selectedItemStack - maxItemStacks;
        }
        else if(selectedItemStack < 0)
        {
          selectedItemStack = maxItemStacks + selectedItemStack;
        }
      }

      void ItemSelectionWheel::next()
      {
        selectedItemStack++;
        checkSelection();
        setTransitions();
      }

      void ItemSelectionWheel::previous()
      {
        selectedItemStack--;
        checkSelection();
        setTransitions();
      }

      ItemStack* ItemSelectionWheel::getSelectedItem() const
      {
        return inventory->getItemStack(selectedItemStack);
      }

      void ItemSelectionWheel::setTransitions()
      {
        for(int i=-3;i<=3;i++)
        {
          int index = selectedItemStack + i;
          if(index < 0)
          {
            index = maxItemStacks + index;
          }
          else if(index >= maxItemStacks)
          {
            index = index - maxItemStacks;
          }

          float tx;
          float ty;
          getTargetPosition(i, &tx, &ty);
          GuiItemDisplay* itemDisplay = *(itemDisplays + index);
          tx = tx - (itemDisplay->width/2.0);

          itemDisplay->setTransition(new GuiTranslationTransition(0.1, itemDisplay->x, itemDisplay->y, tx, ty));
        }
      }
    }
  }
}
