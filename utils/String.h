#ifndef STRING_H
#define STRING_H

#include "LinkedList.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class String
      {
      private:
        LinkedList<char> chars;
      public:
        String();
        String(const char*);
        String(int, int);
        String(const LinkedList<char>&);
        String(const String&);
        String& operator=(const String&);
        operator double() const;
        operator float() const;
        operator int() const;
        int size() const;
        void toChars(char*) const;
        void print() const;
        void addChar(char);
        void replace(const char*, const char*);
        LinkedList<String> split(const char*) const;
        bool isEmpty() const;
        LinkedListIterator<char> getIterator() const;
        const LinkedList<char>& toList() const;
        char getFirstVisibleChar() const;
        void trim();

        bool operator==(const String&) const;
        void operator+=(const String&);
        String operator+(const String&) const;
      };

      String operator+(const String&, const char*);
      String operator+(const char*, const String&);

      String fileToString(const char*);
      String fileToString(const String&);
    }
  }
}

#endif
