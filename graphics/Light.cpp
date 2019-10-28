#include "Light.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      Light::Light(const Vector3& position, const Vector3& color)
      {
        this->position = position;
        this->color = color;
      }

      Light::Light(const Light& light)
      {
        position = light.position;
        color = light.color;
      }

      Light& Light::operator=(const Light& light)
      {
        position = light.position;
        color = light.color;
        return *this;
      }

      Vector3& Light::getPosition()
      {
        return position;
      }

      Vector3& Light::getColor()
      {
        return color;
      }
    }
  }
}
