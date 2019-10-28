#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      class Quaternion
      {
      private:
        float a;
        float b;
        float c;
        float d;
      public:
        Quaternion();
        Quaternion(float, float, float, float);
        Quaternion(const Matrix4x4&);
        Quaternion(const Vector3&);
        Quaternion(float, const Vector3&);
        Quaternion(const Quaternion&);
        Quaternion& operator=(const Quaternion&);
        float& getA();
        float& getB();
        float& getC();
        float& getD();
        Quaternion conjugate() const;
        Quaternion sq(const Quaternion&) const;
        Vector3 rotate(const Vector3&) const;
        Matrix3x3 toMatrix3x3() const;
        Matrix4x4 toMatrix4x4() const;
        float dot(const Quaternion&) const;
        Quaternion slerp(float, const Quaternion&) const;

        Quaternion operator+(const Quaternion&) const;
        Quaternion operator-(const Quaternion&) const;
        Quaternion operator*(const Quaternion&) const;
        Quaternion operator-() const;
        void operator*=(float);
      };
      Quaternion operator*(Quaternion&, float);
      Quaternion operator*(float, Quaternion&);
    }
  }
}

#endif
