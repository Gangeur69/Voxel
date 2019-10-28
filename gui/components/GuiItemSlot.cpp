#include "GuiItemSlot.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace components
      {
        GuiItemSlot::GuiItemSlot(GuiItemHolder* itemHolder, ItemStack* itemStack, Font* font) : GuiComponent(), itemName(font, 0.3, true), itemAmount(font, 0.25, true)
        {
          this->itemHolder = itemHolder;
          this->itemStack = itemStack;
          this->font = font;

          width = itemHolder->width;
          height = itemHolder->height;

          updateText();
        }

        GuiItemSlot::GuiItemSlot(const GuiItemSlot& itemSlot) : GuiComponent(itemSlot), itemName(font, 0.3, true), itemAmount(font, 0.25, true)
        {
          itemHolder = itemSlot.itemHolder;
          itemStack = itemSlot.itemStack;
          font = itemSlot.font;
          updateText();
        }

        GuiItemSlot& GuiItemSlot::operator=(const GuiItemSlot& itemSlot)
        {
          GuiComponent::operator=(itemSlot);
          itemHolder = itemSlot.itemHolder;
          itemStack = itemSlot.itemStack;
          font = itemSlot.font;
          itemName = itemSlot.itemName;
          itemAmount = itemSlot.itemAmount;
          return *this;
        }

        void GuiItemSlot::updateText()
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

        void GuiItemSlot::swapItemStacks()
        {
          Item* newItem = itemHolder->getItem();
          int newAmount = itemHolder->getItemAmount();
          itemHolder->setItem(itemStack->amount, itemStack->item);
          itemStack->amount = newAmount;
          itemStack->item = newItem;
          updateText();
        }

        void GuiItemSlot::onLeftClick()
        {
          GuiComponent::onLeftClick();
          swapItemStacks();
        }

        void GuiItemSlot::render(GuiRenderer* renderer, float parentx, float parenty)
        {
          GuiComponent::render(renderer, parentx, parenty);
          renderer->renderPanel(0.06, parentx + x, parenty + y, width, height, Vector3(1.0,1.0,1.0));
          if(!itemStack->isEmpty())
          {
            float itemBorder = 0.1*width;

            renderer->renderIcon(itemStack->item->getMesh(), itemStack->item->getTexture(),parentx + x + itemBorder, parenty + y + itemBorder, width - 2.0*itemBorder, height - 2.0*itemBorder, Vector3(1.0,1.0,1.0));
          }

          renderer->renderText(parentx + x, parenty + y, itemName);
          renderer->renderText(parentx + x, parenty + y + height - itemAmount.getHeight(), itemAmount);
        }
      }
    }
  }
}
