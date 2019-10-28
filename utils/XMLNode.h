#ifndef XMLNODE_H
#define XMLNODE_H

#include "String.h"
#include "LinkedList.h"
#include "XMLNodeAttribute.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class XMLNode
      {
      private:
        String name;
        String data;
        LinkedList<XMLNodeAttribute> attributes;
        LinkedList<XMLNode> nodes;
      public:
        XMLNode(const String&, const LinkedList<XMLNodeAttribute>&, const LinkedList<XMLNode>&);
        XMLNode(const String&, const LinkedList<XMLNodeAttribute>&, const String&);
        XMLNode(const XMLNode&);
        XMLNode& operator=(const XMLNode&);
        const String& getName() const;
        const String& getAttribute(const String&) const;
        const String& getData() const;
        const XMLNode& get(int, const String&) const;
        const XMLNode& getByAttribute(const String&, const String&, const String&) const;
        LinkedList<const XMLNode*> getChildren(const String&) const;

        const XMLNode& operator[](const String&) const;
        int getNodeAmount(const String&) const;
      };
    }
  }
}

#endif
