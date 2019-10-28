#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "SquareMatrix.h"
#include "Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      class Matrix4x4 : public SquareMatrix
      {
      public:
        Matrix4x4();
        Matrix4x4(int, int, float, float, float, float);
        Vector3 operator*(const Vector3&) const;
        Matrix4x4 operator*(const Matrix4x4&) const;
        Vector3 getScale() const;
        void unScale();
      };
    }
  }
}

#endif
