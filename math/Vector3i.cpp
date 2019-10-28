#include "Vector3i.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      Vector3i::Vector3i(int x, int y, int z)
      {
        this->x = x;
        this->y = y;
        this->z = z;
      }

      Vector3i::Vector3i(const Vector3i& v)
      {
        x = v.x;
        y = v.y;
        z = v.z;
      }

      Vector3i& Vector3i::operator=(const Vector3i& v)
      {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
      }

      int& Vector3i::getX()
      {
        return x;
      }

      int& Vector3i::getY()
      {
        return y;
      }

      int& Vector3i::getZ()
      {
        return z;
      }
    }
  }
}
