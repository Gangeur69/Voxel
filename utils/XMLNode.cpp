#include "XMLNode.h"
#include <iostream>
#include <stdlib.h>

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      XMLNode::XMLNode(const String& name, const LinkedList<XMLNodeAttribute>& attributes, const LinkedList<XMLNode>& nodes)
      {
        this->name = name;
        this->attributes = attributes;
        this->nodes = nodes;
      }

      XMLNode::XMLNode(const String& name, const LinkedList<XMLNodeAttribute>& attributes, const String& data)
      {
        this->name = name;
        this->attributes = attributes;
        this->nodes = nodes;
        this->data = data;
      }

      XMLNode::XMLNode(const XMLNode& node)
      {
        name = node.name;
        attributes = node.attributes;
        nodes = node.nodes;
        data = node.data;
      }

      XMLNode& XMLNode::operator=(const XMLNode& node)
      {
        name = node.name;
        attributes = node.attributes;
        nodes = node.nodes;
        data = node.data;
        return *this;
      }

      const String& XMLNode::getAttribute(const String& string) const
      {
        for(LinkedListIterator<XMLNodeAttribute> itt = attributes.getIterator();itt.isValid();itt.next())
        {
          if(itt.getElement().getName() == string)
          {
            return itt.getElement().getValue();
          }
        }
        (String("Error: <") + string + String("> is a non existant xml attribute!")).print();
        exit(EXIT_FAILURE);
      }

      int XMLNode::getNodeAmount(const String& string) const
      {
        int i = 0;
        for(LinkedListIterator<XMLNode> itt = nodes.getIterator();itt.isValid();itt.next())
        {
          if(itt.getElement().getName() == string)
          {
            i++;
          }
        }
        return i;
      }

      const XMLNode& XMLNode::get(int index, const String& string) const
      {
        int i = 0;
        for(LinkedListIterator<XMLNode> itt = nodes.getIterator();itt.isValid();itt.next())
        {
          if(itt.getElement().getName() == string)
          {
            if(i == index)
            {
              return itt.getElement();
            }
            else
            {
              i++;
            }
          }
        }

        (String("Error: <") + string + String(": ") + String(index, 10) + String("> is a non existant xml node!")).print();
        exit(EXIT_FAILURE);
      }

      const XMLNode& XMLNode::getByAttribute(const String& name, const String& attrib, const String& attribValue) const
      {
        int i=0;
        while(!(get(i, name).getAttribute(attrib) == attribValue))
        {
          i++;
        }
        return get(i, name);
      }

      LinkedList<const XMLNode*> XMLNode::getChildren(const String& string) const
      {
        LinkedList<const XMLNode*> children;
        for(LinkedListIterator<XMLNode> itt = nodes.getIterator();itt.isValid();itt.next())
        {
          if(itt.getElement().getName() == string)
          {
            children.add(&itt.getElement());
          }
        }
        return children;
      }

      const XMLNode& XMLNode::operator[](const String& string) const
      {
        return get(0, string);
      }

      const String& XMLNode::getData() const
      {
        return data;
      }

      const String& XMLNode::getName() const
      {
        return name;
      }
    }
  }
}
