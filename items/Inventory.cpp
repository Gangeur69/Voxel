#include "Inventory.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {

      Inventory::Inventory(int width, int height)
      {
        this->width = width;
        this->height = height;
        generateStacks();
      }

      Inventory::~Inventory()
      {
        deleteStacks();
      }

      Inventory::Inventory(const Inventory& inventory)
      {
        width = inventory.width;
        height = inventory.height;
        generateStacks();
        int size = getSize();
        for(int i=0;i<size;i++)
        {
          *(itemStacks + i) = *(inventory.itemStacks + i);
        }
      }

      Inventory& Inventory::operator=(const Inventory& inventory)
      {
        deleteStacks();
        width = inventory.width;
        height = inventory.height;
        generateStacks();
        int size = getSize();
        for(int i=0;i<size;i++)
        {
          *(itemStacks + i) = *(inventory.itemStacks + i);
        }
        return *this;
      }

      void Inventory::deleteStacks()
      {
        if(itemStacks != NULL)
        {
          delete[] itemStacks;
        }
      }

      void Inventory::generateStacks()
      {
        int size = width*height;
        itemStacks = new ItemStack[size];
      }

      int Inventory::getSize() const
      {
        return width*height;
      }

      void Inventory::setItemStack(int i, const ItemStack& stack)
      {
        if(i >= 0 && i < getSize())
        {
          *(itemStacks + i) = stack;
        }
        else
        {
          throw("ERROR OUT OF INVENTORY BOUNDS!");
        }
      }

      ItemStack* Inventory::getItemStack(int i) const
      {
        if(i >= 0 && i < getSize())
        {
          return itemStacks + i;
        }
        else
        {
          throw("ERROR OUT OF INVENTORY BOUNDS!");
        }
        return NULL;
      }

      int Inventory::getWidth() const
      {
        return width;
      }
    }
  }
}
