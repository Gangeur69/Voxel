#ifndef XMLNODEATTRIBUTE_H
#define XMLNODEATTRIBUTE_H

#include "String.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class XMLNodeAttribute
      {
      private:
        String name;
        String value;
      public:
        XMLNodeAttribute(const String&, const String&);
        XMLNodeAttribute(const XMLNodeAttribute&);
        XMLNodeAttribute& operator=(const XMLNodeAttribute&);
        const String& getName() const;
        const String& getValue() const;
      };
    }
  }
}

#endif
