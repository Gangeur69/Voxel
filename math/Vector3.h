#ifndef VECTOR3_H
#define VECTOR3_H

#include "Vector.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      class Vector3 : public Vector
      {
      public:
        Vector3();
        Vector3(float, float, float);
        float& getX() const;
        float& getY() const;
        float& getZ() const;
        float dot(const Vector3&) const;
        Vector3 cross(const Vector3&) const;

        Vector3 operator+(const Vector3&) const;
        Vector3 operator-(const Vector3&) const;
        Vector3 operator-() const;
      };

      Vector3 operator*(float, const Vector3&);
      Vector3 operator*(const Vector3&, float);
    }
  }
}

#endif
