#include "GuiItemDisplay.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace components
      {
        GuiItemDisplay::GuiItemDisplay(ItemStack* itemStack, Font* font) : GuiComponent(), itemName(font, 0.3, true), itemAmount(font, 0.25, true)
        {
          this->itemStack = itemStack;
          width = 0.2;
          height = 0.2;
        }

        GuiItemDisplay::GuiItemDisplay(const GuiItemDisplay& itemDisplay) : GuiComponent(itemDisplay), itemName(itemDisplay.itemName), itemAmount(itemDisplay.itemAmount)
        {
          itemStack = itemDisplay.itemStack;
        }

        GuiItemDisplay& GuiItemDisplay::operator=(const GuiItemDisplay& itemDisplay)
        {
          GuiComponent::operator=(itemDisplay);
          itemStack = itemDisplay.itemStack;
          itemName = itemDisplay.itemName;
          itemAmount = itemDisplay.itemAmount;
          return *this;
        }

        void GuiItemDisplay::updateText()
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

        void GuiItemDisplay::render(GuiRenderer* renderer, float parentx, float parenty)
        {
          updateText();

          GuiComponent::render(renderer, parentx, parenty);

          renderer->renderPanel(0.06, parentx + x, parenty + y, width, height, Vector3(1.0,1.0,1.0));
          if(!itemStack->isEmpty())
          {
            float itemBorder = 0.1*width;

            renderer->renderIcon(itemStack->item->getMesh(), itemStack->item->getTexture(),parentx + x + itemBorder, parenty + y + itemBorder, width - 2.0*itemBorder, height - 2.0*itemBorder, Vector3(1.0,1.0,1.0));

            renderer->renderText(parentx + x, parenty + y, itemName);
            renderer->renderText(parentx + x, parenty + y + height - itemAmount.getHeight(), itemAmount);
          }
        }
      }
    }
  }
}
