#include "XMLNodeAttribute.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      XMLNodeAttribute::XMLNodeAttribute(const String& name, const String& value)
      {
        this->name = name;
        this->value = value;
      }

      XMLNodeAttribute::XMLNodeAttribute(const XMLNodeAttribute& attribute)
      {
        name = attribute.name;
        value = attribute.value;
      }

      XMLNodeAttribute& XMLNodeAttribute::operator=(const XMLNodeAttribute& attribute)
      {
        name = attribute.name;
        value = attribute.value;
        return *this;
      }

      const String& XMLNodeAttribute::getName() const
      {
        return name;
      }

      const String& XMLNodeAttribute::getValue() const
      {
        return value;
      }
    }
  }
}
