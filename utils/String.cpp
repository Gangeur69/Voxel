#include "String.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {

      String::String()
      {

      }

      String::String(const char* data)
      {
        int i = 0;
        char c = *(data + i);
        while(c != '\0')
        {
          chars.add(c);
          i++;
          c = *(data + i);
        }
      }

      String::String(int x, int size)
      {
        char* data = new char[size];
        sprintf(data,"%d",x);

        int i = 0;
        char c = *(data + i);
        while(c != '\0')
        {
          chars.add(c);
          i++;
          c = *(data + i);
        }

        delete[] data;
      }

      String::String(const LinkedList<char>& chars)
      {
        this->chars = chars;
      }

      String::String(const String& string)
      {
        chars = string.chars;
      }

      String& String::operator=(const String& string)
      {
        chars = string.chars;
        return *this;
      }

      String::operator double() const
      {
        int amount = size();
        char ptr[amount + 1];
        *(ptr + amount) = '\0';
        toChars(ptr);
        return atof(ptr);
      }

      String::operator float() const
      {
        double res = *this;
        return res;
      }

      String::operator int() const
      {
        int amount = size();
        char ptr[amount + 1];
        *(ptr + amount) = '\0';
        toChars(ptr);
        return atoi(ptr);
      }

      int String::size() const
      {
        return chars.size();
      }

      void String::toChars(char* ptr) const
      {
        int i = 0;
        for(LinkedListIterator<char> itt = chars.getIterator(); itt.isValid();itt.next())
        {
          *(ptr + i) = itt.getElement();
          i++;
        }
      }

      void String::print() const
      {
        int amount = size();
        char ptr[amount + 1];
        *(ptr + amount) = '\0';
        toChars(ptr);
        std::cout << ptr << std::endl;
      }

      void String::addChar(char c)
      {
        chars.add(c);
      }

      void String::replace(const char* fromData, const char* toData)
      {
        String from(fromData);
        String to(toData);
        int fromSize = from.size();
        int toSize = to.size();
        if(fromSize == 0)
        {
          std::cerr << "FATAL ERROR: trying to replace empty sting!" << std::endl;
          exit(EXIT_FAILURE);
        }

        LinkedListIterator<char> itt = chars.getIterator();
        if(isSubList<char>(itt, from.chars))
        {
          chars.removeAmount(0, fromSize);
          chars.insert(0, to.chars);
          itt = chars.getIterator();
          itt.skip(toSize-1);
        }

        while(itt.isValid())
        {
          if(nextIsSubList<char>(itt, from.chars))
          {
            chars.removeAmount(itt.getAdress(), fromSize);
            chars.insert(itt.getAdress(), to.chars);
            itt.skip(toSize-1);
          }
          itt.next();
        }
      }

      LinkedList<String> String::split(const char* rejexData) const
      {
        String rejex(rejexData);
        int rejexSize = rejex.size();
        if(rejexSize == 0)
        {
          std::cerr << "FATAL ERROR: spliting using rejex of size 0!" << std::endl;
          exit(EXIT_FAILURE);
        }
        LinkedList<String> res;
        LinkedListIterator<char> itt = chars.getIterator();
        res.add(String(getListTo<char>(itt, rejex.chars)));
        while(itt.isValid())
        {
          itt.skip(rejexSize);
          res.add(String(getListTo<char>(itt, rejex.chars)));
        }
        return res;
      }

      bool String::isEmpty() const
      {
        return chars.isEmpty();
      }

      LinkedListIterator<char> String::getIterator() const
      {
        return chars.getIterator();
      }

      const LinkedList<char>& String::toList() const
      {
        return chars;
      }

      char String::getFirstVisibleChar() const
      {
        for(LinkedListIterator<char> itt = chars.getIterator();itt.isValid();itt.next())
        {
          if(isprint(itt.getElement()) && itt.getElement() != ' ')
          {
            return itt.getElement();
          }
        }
        return '\0';
      }

      void String::trim()
      {
        while(!chars.isEmpty() && chars.getFirst() == ' ')
        {
          chars.removeFirst();
        }

        while(!chars.isEmpty() && chars.getLast() == ' ')
        {
          chars.remove(chars.size()-1);
        }
      }

      bool String::operator==(const String& string) const
      {
        return chars == string.chars;
      }

      void String::operator+=(const String& string)
      {
        chars+=string.chars;
      }

      String String::operator+(const String& string) const
      {
        String result = *this;
        result+=string;
        return result;
      }

      String operator+(const String& string, const char* data)
      {
        return string + String(data);
      }

      String operator+(const char* data, const String& string)
      {
        return String(data) + string;
      }

      String fileToString(const char* fileName)
      {
        FILE* file = fopen(fileName, "r");
        if(file == NULL)
        {
          std::cout << "Error: " << fileName << " was not found!" << std::endl;
          exit(EXIT_FAILURE);
        }
        fseek(file, 0, SEEK_END);
        int fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        std::cout << "Size of " << fileName << ": " << fileSize << std::endl;

        String data;
        int c;
        c = fgetc(file);
        while(c != EOF)
        {
          data.addChar((char)c);
          c = fgetc(file);
        }
        fclose(file);
        std::cout << fileName << " was read correctly!" << std::endl;
        return data;
      }

      String fileToString(const String& fileNameStr)
      {
        int amount = fileNameStr.size();
        char fileName[amount + 1];
        *(fileName + amount) = '\0';
        fileNameStr.toChars(fileName);
        return fileToString(fileName);
      }

    }
  }
}
