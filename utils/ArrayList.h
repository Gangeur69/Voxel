#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>

namespace gt
{
  namespace doubovik
  {

    template<typename Type> class ArrayList
    {
    private:
      int memorySize;
      int amount;
      Type** array;
    public:

      ArrayList()
      {
        memorySize = 1;
        amount = 0;
        array = new Type*[memorySize];
      }

      ~ArrayList()
      {
        for(int i=0;i<amount;i++)
        {
          delete *(array + i);
        }
        delete [] array;
      }

      ArrayList(const ArrayList& list)
      {
        memorySize = list.memorySize;
        amount = list.amount;
        array = new Type*[memorySize];
        for(int i=0;i<amount;i++)
        {
          *(array + i) = new Type(**(list.array + i));
        }
      }

      ArrayList& operator=(const ArrayList& list)
      {
        for(int i=0;i<amount;i++)
        {
          delete *(array + i);
        }
        delete [] array;

        memorySize = list.memorySize;
        amount = list.amount;
        array = new Type*[memorySize];
        for(int i=0;i<amount;i++)
        {
          *(array + i) = new Type(**(list.array + i));
        }
        return *this;
      }

      void expand(int add)
      {
        if(add <= 0)
        {
          throw("Error expanding by 0 or negative amount!");
        }
        memorySize+=add;
        Type** temp = new Type*[memorySize];
        for(int i=0;i<amount;i++)
        {
          *(temp + i) = *(array + i);
        }

        delete [] array;
        array = temp;
      }

      void add(const Type& element)
      {
        if(amount >= memorySize)
        {
          expand(memorySize);
        }
        *(array + amount) = new Type(element);
        amount++;
        std::cout << "mem " << memorySize << std::endl;
      }

      int size() const
      {
        return amount;
      }

      Type& operator[](int index) const
      {
        if(index < 0 || index >= amount)
        {
          throw("Error index out of bounds!");
        }
        return **(array + index);
      }
    };

  }
}

#endif
