#ifndef XMLREADER_H
#define XMLREADER_H

#include "String.h"
#include "LinkedList.h"
#include "XMLNodeAttribute.h"
#include "XMLNode.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class XMLReader
      {
      private:
        static String headerStart;
        static String headerEnd;
        static String headerQuit;
        static String space;
        static String equal;
        static String valueContainer;

        static char headerStartChar;
        static char headerQuitChar;
        static char spaceChar;

        LinkedList<XMLNode> nodes;

        void readData(String&);
        LinkedList<XMLNode> readNodes(LinkedListIterator<char>&);
        XMLNode readNode(LinkedListIterator<char>&);
        bool readNodeHeader(LinkedListIterator<char>&, String*, LinkedList<XMLNodeAttribute>*);
        void readNodeName(LinkedListIterator<char>&, String*);
        LinkedList<XMLNodeAttribute> readAttributes(LinkedListIterator<char>&);
        void goToAttribute(LinkedListIterator<char>&);
        XMLNodeAttribute readAttribute(LinkedListIterator<char>&);
      public:
        XMLReader(const char*);
        const XMLNode& get(int, const String&) const;
        const XMLNode& operator[](const String&) const;
      };
    }
  }
}

#endif
