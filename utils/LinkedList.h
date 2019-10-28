#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdlib.h>

namespace gt
{
  namespace doubovik
  {

    //element
    template<typename Type> class LinkedElement
    {
    private:
      Type element;
      LinkedElement<Type>* next;

    public:
      LinkedElement(const Type& element) : element(element)
      {
        this->next = NULL;
      }

      ~LinkedElement()
      {
        next = NULL;
      }

      LinkedElement(const LinkedElement<Type>& linkedElement)
      {
        element = linkedElement.element;
        next = linkedElement.next;
      }

      LinkedElement<Type>& operator=(const LinkedElement<Type>& linkedElement)
      {
        element = linkedElement.element;
        next = linkedElement.next;
        return *this;
      }

      Type& getElement()
      {
        return element;
      }

      LinkedElement<Type>*& getNext()
      {
        return next;
      }

    };

    //itterator
    template<typename Type> class LinkedListIterator
    {
    private:
      LinkedElement<Type>* current;

    public:
      LinkedListIterator(LinkedElement<Type>* start)
      {
        current = start;
      }

      LinkedListIterator(const LinkedListIterator<Type>& iterator)
      {
        current = iterator.current;
      }

      LinkedListIterator<Type>& operator=(const LinkedListIterator<Type>& iterator)
      {
        current = iterator.current;
        return *this;
      }

      void skip(int amount)
      {
        for(int i=0;i<amount;i++)
        {
          if(isValid())
          {
            next();
          }
        }
      }

      bool isValid() const
      {
        return current != NULL;
      }

      void next()
      {
        if(!isValid())
        {
          std::cerr << "Error: itterator is out of bounds!" << std::endl;
          exit(EXIT_FAILURE);
        }
        current = current->getNext();
      }

      Type& getElement() const
      {
        if(!isValid())
        {
          std::cerr << "Error: itterator is out of bounds!" << std::endl;
          exit(EXIT_FAILURE);
        }
        return current->getElement();
      }

      LinkedElement<Type>* getAdress() const
      {
        return current;
      }

      void toElement(const Type& element)
      {
        while(isValid() && getElement() != element)
        {
          next();
        }
      }
    };

    //list
    template<typename Type> class LinkedList
    {
    private:
      LinkedElement<Type>* first;
      LinkedElement<Type>* last;

      void linkToNext(LinkedElement<Type>* linkedElement, int amount)
      {
        for(int i=0;i<amount;i++)
        {
          LinkedElement<Type>* toDelete = linkedElement->getNext();
          if(toDelete != NULL)
          {
            if(toDelete == last)
            {
              last = linkedElement;
            }
            linkedElement->getNext() = toDelete->getNext();
            delete toDelete;
          }
          else
          {
            std::cerr << "Error: " << amount << " linking to next out of bounds!" << std::endl;
            exit(EXIT_FAILURE);
          }
        }
      }

      LinkedElement<Type>* getLinkedElement(int index)
      {
        LinkedElement<Type>* current = first;
        for(int i=0;i<index;i++)
        {
          if(current->getNext() != NULL)
          {
            current = current->getNext();
          }
          else
          {
            std::cerr << "Error: getting linked element " << index << " index is out bounds!" << std::endl;
            exit(EXIT_FAILURE);
          }
        }
        return current;
      }

    public:
      LinkedList()
      {
        first = NULL;
        last = NULL;
      }

      ~LinkedList()
      {
        LinkedElement<Type>* linkedElement = first;
        while(linkedElement != NULL)
        {
          LinkedElement<Type>* toDelete = linkedElement;
          linkedElement = toDelete->getNext();
          delete toDelete;
        }
      }

      LinkedList(const LinkedList<Type>& list)
      {
        first = NULL;
        last = NULL;
        for(LinkedListIterator<Type> itt = list.getIterator(); itt.isValid(); itt.next())
        {
          add(itt.getElement());
        }
      }

      LinkedList<Type>& operator=(const LinkedList<Type>& list)
      {
        LinkedElement<Type>* linkedElement = first;
        while(linkedElement != NULL)
        {
          LinkedElement<Type>* toDelete = linkedElement;
          linkedElement = toDelete->getNext();
          delete toDelete;
        }
        first = NULL;
        last = NULL;
        for(LinkedListIterator<Type> itt = list.getIterator(); itt.isValid(); itt.next())
        {
          add(itt.getElement());
        }
        return *this;
      }

      LinkedListIterator<Type> getIterator() const
      {
        return LinkedListIterator<Type>(first);
      }

      Type& get(int index)
      {
        return getLinkedElement(index)->getElement();
      }

      Type& getLast() const
      {
        if(last == NULL)
        {
          std::cerr << "Error: list is empty!" << std::endl;
          exit(EXIT_FAILURE);
        }
        return last->getElement();
      }

      Type& getFirst() const
      {
        if(first == NULL)
        {
          std::cerr << "Error: list is empty!" << std::endl;
          exit(EXIT_FAILURE);
        }
        return first->getElement();
      }

      void clear()
      {
        LinkedElement<Type>* linkedElement = first;
        while(linkedElement != NULL)
        {
          LinkedElement<Type>* toDelete = linkedElement;
          linkedElement = toDelete->getNext();
          delete toDelete;
        }
        first = NULL;
        last = NULL;
      }

      void add(const Type& element)
      {
        if(last != NULL)
        {
          last->getNext() = new LinkedElement<Type>(element);
          last = last->getNext();
        }
        else if(first == NULL)
        {
          first = new LinkedElement<Type>(element);
          last = first;
        }
        else
        {
          std::cerr<< "ERROR: non existant last element, but first element exists!" << std::endl;
          exit(EXIT_FAILURE);
        }
      }

      void addAsFirst(const Type& element)
      {
        LinkedElement<Type>* newFirst = new LinkedElement<Type>(element);
        if(first == NULL)
        {
          last = newFirst;
        }
        newFirst->getNext() = first;
        first = newFirst;
      }

      void removeFirst()
      {
        if(first != NULL)
        {
          if(first == last)
          {
            last = NULL;
          }
          LinkedElement<Type>* temp = first;
          first = first->getNext();
          delete temp;
        }
        else
        {
          std::cerr << "Error: Index out of bounds, non existant first element!" << std::endl;
          exit(EXIT_FAILURE);
        }
      }

      bool contains(const Type& element) const
      {
        for(LinkedListIterator<Type> itt = getIterator();itt.isValid();itt.next())
        {
          if(itt.getElement() == element)
          {
            return true;
          }
        }
        return false;
      }

      void removeElement(const Type& element)
      {
        if(element == first->getElement())
        {
          removeFirst();
        }
        else
        {
          LinkedElement<Type>* current = first;
          while(current->getNext()->getElement() != element)
          {
            current = current->getNext();
          }
          if(current->getNext() != NULL)
          {
            linkToNext(current, 1);
          }
        }
      }

      void remove(int index)
      {
        removeAmount(index, 1);
      }

      void removeAmount(int index, int amount)
      {
        if(index == 0)
        {
          for(int i=0;i<amount;i++)
          {
            removeFirst();
          }
        }
        else
        {
          LinkedElement<Type>* before = getLinkedElement(index-1);
          linkToNext(before, amount);
        }
      }

      void removeAmount(LinkedElement<Type>* before, int amount)
      {
        linkToNext(before, amount);
      }

      void insert(int index, const Type& element)
      {
        if(index == 0)
        {
          addAsFirst(element);
        }
        else
        {
          LinkedElement<Type>* before = getLinkedElement(index-1);
          LinkedElement<Type>* toInsert = new LinkedElement<Type>(element);
          toInsert->getNext() = before->getNext();
          before->getNext() = toInsert;
          if(before == last)
          {
            last = toInsert;
          }
        }
      }

      void insert(LinkedElement<Type>* before, const LinkedList<Type>& elements)
      {
        for(LinkedListIterator<Type> itt = elements.getIterator();itt.isValid();itt.next())
        {
          LinkedElement<Type>* toInsert = new LinkedElement<Type>(itt.getElement());
          toInsert->getNext() = before->getNext();
          before->getNext() = toInsert;
          if(before == last)
          {
            last = toInsert;
          }
          before = toInsert;
        }
      }

      void insert(int index, const LinkedList<Type>& elements)
      {
        if(index == 0)
        {
          LinkedListIterator<Type> itt = elements.getIterator();
          if(!itt.isValid())
          {
            return;
          }
          addAsFirst(itt.getElement());
          itt.next();
          LinkedElement<Type>* before = first;
          while(itt.isValid())
          {
            LinkedElement<Type>* toInsert = new LinkedElement<Type>(itt.getElement());
            toInsert->getNext() = before->getNext();
            before->getNext() = toInsert;
            if(before == last)
            {
              last = toInsert;
            }
            before = toInsert;
            itt.next();
          }
        }
        else
        {
          LinkedElement<Type>* before = getLinkedElement(index-1);
          insert(before, elements);
        }
      }

      int size() const
      {
        int k = 0;
        for(LinkedListIterator<Type> itt = getIterator(); itt.isValid(); itt.next())
        {
          k++;
        }
        return k;
      }

      bool isEmpty() const
      {
        return first == NULL;
      }

      void toArray(Type* array) const
      {
        int k=0;
        for(LinkedListIterator<Type> itt=getIterator();itt.isValid();itt.next())
        {
          *(array + k) = itt.getElement();
          k++;
        }
      }

      int getIndex(const Type& element) const
      {
        int i=0;
        LinkedElement<Type>* current = first;
        while(current != NULL)
        {
          if(current->getElement() == element)
          {
            return i;
          }
          current = current->getNext();
          i++;
        }
        std::cerr << "Index of element in linked list not found!" << std::endl;
        exit(EXIT_FAILURE);
        return -1;
      }

      bool operator==(const LinkedList<Type>& list) const
      {
        LinkedElement<Type>* current1 = first;
        LinkedElement<Type>* current2 = list.first;

        while(current1 != NULL && current2 != NULL)
        {
          if(current1->getElement() != current2->getElement())
          {
            return false;
          }
          current1 = current1->getNext();
          current2 = current2->getNext();
        }

        return current1 == NULL && current2 == NULL;
      }

      void operator+=(const LinkedList<Type>& list)
      {
        for(LinkedListIterator<Type> itt = list.getIterator();itt.isValid();itt.next())
        {
          add(itt.getElement());
        }
      }

      LinkedList<Type> operator+(const LinkedList<Type>& list)
      {
        LinkedList<Type> result = *this;
        for(LinkedListIterator<Type> itt = list.getIterator();itt.isValid();itt.next())
        {
          result.add(itt.getElement());
        }
        return result;
      }
    };

    template<typename Type> bool isSubList(LinkedListIterator<Type> itt1, const LinkedList<Type>& list)
    {
      for(LinkedListIterator<Type> itt2 = list.getIterator();itt2.isValid();itt2.next())
      {
        if(!itt1.isValid())
        {
          return false;
        }
        else if(itt1.getElement() != itt2.getElement())
        {
          return false;
        }
        itt1.next();
      }
      return true;
    }

    template<typename Type> bool nextIsSubList(LinkedListIterator<Type> itt1, const LinkedList<Type>& list)
    {
      itt1.next();
      for(LinkedListIterator<Type> itt2 = list.getIterator();itt2.isValid();itt2.next())
      {
        if(!itt1.isValid())
        {
          return false;
        }
        else if(itt1.getElement() != itt2.getElement())
        {
          return false;
        }
        itt1.next();
      }
      return true;
    }

    template<typename Type> LinkedList<Type> getListTo(LinkedListIterator<Type>& itt, const LinkedList<Type>& list)
    {
      LinkedList<Type> res;
      while(itt.isValid())
      {
        if(isSubList<Type>(itt, list))
        {
          return res;
        }
        res.add(itt.getElement());
        itt.next();
      }
      return res;
    }

    template<typename Type> LinkedList<Type> getListTo(LinkedListIterator<Type>& itt, const Type& element)
    {
      LinkedList<Type> res;
      while(itt.isValid() && itt.getElement() != element)
      {
        res.add(itt.getElement());
        itt.next();
      }
      return res;
    }

    template<typename Type> void skipTo(LinkedListIterator<Type>& itt, const LinkedList<Type>& list)
    {
      while(itt.isValid())
      {
        if(isSubList<Type>(itt, list))
        {
          return;
        }
        itt.next();
      }
    }

    template<typename Type> bool hasNext(LinkedListIterator<Type> itt, const LinkedList<Type>& list)
    {
      while(itt.isValid())
      {
        if(isSubList<Type>(itt, list))
        {
          return true;
        }
      }
      return false;
    }

  }
}

#endif
