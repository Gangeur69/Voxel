#ifndef ITEMSTACK_H
#define ITEMSTACK_H

#include "Item.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      class ItemStack
      {
      public:
        Item* item;
        int amount;

        ItemStack();
        ItemStack(const ItemStack&);
        ItemStack& operator=(const ItemStack);

        Item* getItem() const;
        bool isEmpty() const;
        void clear();
      };
    }
  }
}

#endif
