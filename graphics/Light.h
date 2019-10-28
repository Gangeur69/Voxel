#ifndef LIGHT_H
#define LIGHT_H

#include "../math/Vector3.h"

using namespace gt::doubovik::math;

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      class Light
      {
      private:

        Vector3 position;
        Vector3 color;
      public:
        Light(const Vector3&, const Vector3&);
        Light(const Light&);
        Light& operator=(const Light&);

        Vector3& getPosition();
        Vector3& getColor();
      };
    }
  }
}

#endif
