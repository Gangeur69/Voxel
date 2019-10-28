#include "InventoryPanel.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      InventoryPanel::InventoryPanel(GuiItemHolder* holder, Inventory* inventory, Font* font) : Panel(), name(String("Inventory"), font, 1.0, 0.6, true)
      {
        this->holder = holder;
        this->inventory = inventory;
        this->font = font;

        x = -1.2;
        y = -0.8;
        width = 2.4;
        height = 1.6;

        generateSlots();
        setTitle(&name);
      }

      InventoryPanel::InventoryPanel(const InventoryPanel& panel) : Panel(panel), name(panel.name)
      {
        holder = panel.holder;
        inventory = panel.inventory;
        font = panel.font;
        generateSlots();
      }

      InventoryPanel& InventoryPanel::operator=(const InventoryPanel& panel)
      {
        Panel::operator=(panel);
        clearComponents();
        int size = inventory->getSize();
        for(int i=0;i<size;i++)
        {
          delete *(slots + i);
        }
        delete[] slots;
        holder = panel.holder;
        inventory = panel.inventory;
        font = panel.font;
        name = panel.name;
        generateSlots();
        return *this;
      }

      InventoryPanel::~InventoryPanel()
      {
        int size = inventory->getSize();
        for(int i=0;i<size;i++)
        {
          delete *(slots + i);
        }
        delete[] slots;
      }

      void InventoryPanel::generateSlots()
      {
        int size = inventory->getSize();
        slots = new GuiItemSlot*[size];

        int lineCount = 0;

        float startx = (width - inventory->getWidth()*holder->width - (inventory->getWidth() - 1)*0.02)/2.0;

        float ix = startx;
        float iy = height - holder->height - 0.02;

        for(int i=0;i<size;i++)
        {
          *(slots + i) = new GuiItemSlot(holder, inventory->getItemStack(i), font);
          (*(slots + i))->x = ix;
          (*(slots + i))->y = iy;
          addComponent(*(slots + i));

          lineCount++;
          if(lineCount >= inventory->getWidth())
          {
            lineCount = 0;
            ix = startx;
            iy -= holder->height + 0.02;
          }
          else
          {
            ix += holder->width + 0.02;
          }
        }
      }
    }
  }
}
