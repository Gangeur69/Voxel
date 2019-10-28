#include "XMLReader.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {

      String XMLReader::headerStart = String("<");
      String XMLReader::headerEnd = String(">");
      String XMLReader::headerQuit = String("/");
      String XMLReader::space = String(" ");
      String XMLReader::equal = String("=");
      String XMLReader::valueContainer = String("\"");

      char XMLReader::headerStartChar = '<';
      char XMLReader::headerQuitChar = '/';
      char XMLReader::spaceChar = ' ';

      XMLReader::XMLReader(const char* fileName)
      {
        std::cout << "here?" << std::endl;
        String data = fileToString(fileName);
        std::cout << "here? 2" << std::endl;
        readData(data);
      }

      void XMLReader::readData(String& data)
      {
        std::cout << "Unpacking xml data..." << std::endl;

        LinkedListIterator<char> itt = data.getIterator();
        nodes = readNodes(itt);
        std::cout << "Done unpacking xml data! / parent nodes: " << nodes.size() << std::endl;
      }

      LinkedList<XMLNode> XMLReader::readNodes(LinkedListIterator<char>& itt)
      {
        String endNode("</");
        LinkedList<XMLNode> nodes;
        while(itt.isValid())
        {
          itt.toElement('<');
          if(!itt.isValid())
          {
            return nodes;
          }
          if(itt.getElement() != '<')
          {
            std::cerr << "Invalid xml node format!" << std::endl;
            exit(EXIT_FAILURE);
          }
          if(isSubList(itt, endNode.toList()))
          {
            return nodes;
          }
          nodes.add(readNode(itt));
        }
        return nodes;
      }

      XMLNode XMLReader::readNode(LinkedListIterator<char>& itt)
      {
        itt.next();
        if(!itt.isValid())
        {
          std::cerr << "Invalid xml node format!" << std::endl;
          exit(EXIT_FAILURE);
        }
        String name;
        LinkedList<XMLNodeAttribute> attributes;
        if(!readNodeHeader(itt, &name, &attributes))
        {
          itt.next();
          if(!itt.isValid() || itt.getElement() != '>')
          {
            std::cerr << "Invalid xml node format!" << std::endl;
            exit(EXIT_FAILURE);
          }
          return XMLNode(name, attributes, String(""));
        }
        name.print();
        String nodeEnd = "</" + name + ">";
        nodeEnd.print();
        itt.next();
        if(!itt.isValid())
        {
          std::cerr << "Invalid xml node format!" << std::endl;
          exit(EXIT_FAILURE);
        }
        String data(getListTo(itt, '<'));
        LinkedList<XMLNode> nodes = readNodes(itt);
        if(!itt.isValid() || !isSubList(itt, nodeEnd.toList()))
        {
          std::cerr << "Invalid xml node format!" << std::endl;
          exit(EXIT_FAILURE);
        }
        itt.skip(nodeEnd.size());
        if(nodes.size() == 0)
        {
          return XMLNode(name, attributes, data);
        }
        return XMLNode(name, attributes, nodes);
      }

      //complete
      bool XMLReader::readNodeHeader(LinkedListIterator<char>& itt, String* name, LinkedList<XMLNodeAttribute>* attributes)
      {
        readNodeName(itt, name);
        if(itt.getElement() == '/')
        {
          return false;
        }
        else if(itt.getElement() == '>')
        {
          return true;
        }
        itt.next();
        if(!itt.isValid())
        {
          std::cerr << "Invalid xml node format!" << std::endl;
          exit(EXIT_FAILURE);
        }
        *attributes = readAttributes(itt);
        if(itt.getElement() == '/')
        {
          return false;
        }
        return true;
      }

      //complete
      LinkedList<XMLNodeAttribute> XMLReader::readAttributes(LinkedListIterator<char>& itt)
      {
        LinkedList<XMLNodeAttribute> attributes;
        while(itt.isValid())
        {
          goToAttribute(itt);
          if(itt.getElement() == '>')
          {
            return attributes;
          }
          else if(itt.getElement() == '/')
          {
            return attributes;
          }
          attributes.add(readAttribute(itt));
        }
        std::cerr << "Invalid xml node format!" << std::endl;
        exit(EXIT_FAILURE);
        return attributes;
      }

      //complete
      void XMLReader::goToAttribute(LinkedListIterator<char>& itt)
      {
        while(itt.isValid() && (!isprint(itt.getElement()) || itt.getElement() == ' '))
        {
          itt.next();
        }
        if(!itt.isValid())
        {
          std::cerr << "Invalid xml node format!" << std::endl;
          exit(EXIT_FAILURE);
        }
        if(itt.getElement() == '/' || itt.getElement() == '>')
        {
          return;
        }
      }

      //complete
      XMLNodeAttribute XMLReader::readAttribute(LinkedListIterator<char>& itt)
      {
        String name(getListTo(itt, '='));
        name.print();
        if(!itt.isValid() || itt.getElement() != '=')
        {
          std::cerr << "Invalid xml node format!" << std::endl;
          exit(EXIT_FAILURE);
        }
        itt.toElement('"');
        if(!itt.isValid() || itt.getElement() != '"')
        {
          std::cerr << "Invalid xml node format!" << std::endl;
          exit(EXIT_FAILURE);
        }
        itt.next();
        if(!itt.isValid())
        {
          std::cerr << "Invalid xml node format!" << std::endl;
          exit(EXIT_FAILURE);
        }
        String value(getListTo(itt, '"'));
        itt.next();
        value.print();
        return XMLNodeAttribute(name, value);
      }

      //complete
      void XMLReader::readNodeName(LinkedListIterator<char>& itt, String* name)
      {
        //isprint
        while(itt.isValid())
        {
          if(itt.getElement() == '>')
          {
            return;
          }
          else if(itt.getElement() == '/')
          {
            return;
          }
          else if(itt.getElement() == ' ')
          {
            return;
          }
          name->addChar(itt.getElement());
          itt.next();
        }
        std::cerr << "Invalid xml node format!" << std::endl;
        exit(EXIT_FAILURE);
      }

      const XMLNode& XMLReader::get(int index, const String& string) const
      {
        int i = 0;
        for(LinkedListIterator<XMLNode> itt=nodes.getIterator();itt.isValid();itt.next())
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

        (String("Error: <") + string + String("> is a non existant xml node!")).print();
        exit(EXIT_FAILURE);
      }

      const XMLNode& XMLReader::operator[](const String& string) const
      {
        return get(0, string);
      }

    }
  }
}
