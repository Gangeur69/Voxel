#include "ItemStack.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      ItemStack::ItemStack()
      {
        item = NULL;
        amount = 0;
      }

      ItemStack::ItemStack(const ItemStack& itemStack)
      {
        item = itemStack.item;
        amount = itemStack.amount;
      }

      ItemStack& ItemStack::operator=(const ItemStack itemStack)
      {
        item = itemStack.item;
        amount = itemStack.amount;
        return *this;
      }

      Item* ItemStack::getItem() const
      {
        return item;
      }

      bool ItemStack::isEmpty() const
      {
        if(item == NULL)
        {
          return true;
        }
        return amount <= 0;
      }

      void ItemStack::clear()
      {
        item = NULL;
        amount = 0;
      }
    }
  }
}
