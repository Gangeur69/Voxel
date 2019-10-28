#ifndef INVENTORY_H
#define INVENTORY_H

#include "ItemStack.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      class Inventory
      {
      private:
        int width;
        int height;
        ItemStack* itemStacks;

        void deleteStacks();
        void generateStacks();
      public:
        Inventory(int, int);
        ~Inventory();
        Inventory(const Inventory&);
        Inventory& operator=(const Inventory&);

        int getSize() const;
        void setItemStack(int, const ItemStack&);
        ItemStack* getItemStack(int) const;
        int getWidth() const;
      };
    }
  }
}

#endif
