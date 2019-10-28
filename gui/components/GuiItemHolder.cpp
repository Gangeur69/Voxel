#include "GuiItemHolder.h"

#include "../../math/Vector3.h"

using namespace gt::doubovik::math;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace components
      {
        GuiItemHolder::GuiItemHolder(ItemStack* itemStack, Font* font) : GuiComponent(), itemName(font, 0.3, true), itemAmount(font, 0.25, true)
        {
          this->itemStack = itemStack;
          this->font = font;
          width = 0.2;
          height = 0.2;

          itemName.setColor(1.0, 1.0, 1.0);
          itemAmount.setColor(1.0, 1.0, 1.0);
        }

        GuiItemHolder::GuiItemHolder(const GuiItemHolder& itemHolder) : GuiComponent(itemHolder), itemName(itemHolder.itemName), itemAmount(itemHolder.itemAmount)
        {
          itemStack = itemHolder.itemStack;
          font = itemHolder.font;
        }

        GuiItemHolder& GuiItemHolder::operator=(const GuiItemHolder& itemHolder)
        {
          GuiComponent::operator=(itemHolder);
          itemStack = itemHolder.itemStack;
          font = itemHolder.font;
          itemName = itemHolder.itemName;
          itemAmount = itemHolder.itemAmount;
          return *this;
        }

        void GuiItemHolder::updateText()
        {
          if(!itemStack->isEmpty())
          {
            itemName.setText(itemStack->item->getName(), width);
            if(itemStack->amount > 1)
            {
              itemAmount.setText(String("Amt: ") + String(itemStack->amount, 20), width);
            }
            else
            {
              itemAmount.clear();
            }
          }
          else
          {
            itemName.clear();
            itemAmount.clear();
          }
        }

        void GuiItemHolder::setItem(int amount, Item* item)
        {
          itemStack->amount = amount;
          itemStack->item = item;
          updateText();
        }

        Item* GuiItemHolder::getItem() const
        {
          return itemStack->item;
        }

        int GuiItemHolder::getItemAmount() const
        {
          return itemStack->amount;
        }

        void GuiItemHolder::render(GuiRenderer* renderer, float parentx, float parenty)
        {
          GuiComponent::render(renderer, parentx, parenty);
          if(!itemStack->isEmpty())
          {
            renderer->renderPanel(0.06, parentx + x, parenty + y, width, height, Vector3(1.0,1.0,1.0));
            float itemBorder = 0.1*width;

            renderer->renderIcon(itemStack->item->getMesh(), itemStack->item->getTexture(),parentx + x + itemBorder, parenty + y + itemBorder, width - 2.0*itemBorder, height - 2.0*itemBorder, Vector3(1.0,1.0,1.0));
          }
          renderer->renderText(parentx + x, parenty + y, itemName);
          renderer->renderText(parentx + x, parenty + y + height - itemAmount.getHeight(), itemAmount);
        }

        void GuiItemHolder::updateMouseData(bool leftClick, float parentx, float parenty, float mx, float my)
        {
          GuiComponent::updateMouseData(leftClick, parentx, parenty, mx, my);
          x = mx - width/2.0;
          y = my - height/2.0;
        }
      }
    }
  }
}
