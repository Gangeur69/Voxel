#include "Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      Vector3::Vector3() : Vector(3)
      {

      }

      Vector3::Vector3(float x, float y, float z) : Vector(3)
      {
        getX() = x;
        getY() = y;
        getZ() = z;
      }

      float& Vector3::getX() const
      {
        return get(0);
      }

      float& Vector3::getY() const
      {
        return get(1);
      }

      float& Vector3::getZ() const
      {
        return get(2);
      }

      float Vector3::dot(const Vector3& v) const
      {
        return getX()*v.getX() + getY()*v.getY() + getZ()*v.getZ();
      }

      Vector3 Vector3::cross(const Vector3& v) const
      {
        float x = getY()*v.getZ() - getZ()*v.getY();
        float y = getZ()*v.getX() - getX()*v.getZ();
        float z = getX()*v.getY() - getY()*v.getX();
        return Vector3(x, y, z);
      }

      Vector3 Vector3::operator+(const Vector3& v) const
      {
        return Vector3(getX() + v.getX(), getY() + v.getY(), getZ() + v.getZ());
      }

      Vector3 Vector3::operator-(const Vector3& v) const
      {
        return Vector3(getX() - v.getX(), getY() - v.getY(), getZ() - v.getZ());
      }

      Vector3 Vector3::operator-() const
      {
        return Vector3(-getX(), -getY(), -getZ());
      }

      Vector3 operator*(float x, const Vector3& v)
      {
        return Vector3(x*v.getX(), x*v.getY(), x*v.getZ());
      }

      Vector3 operator*(const Vector3& v, float x)
      {
        return x*v;
      }
    }
  }
}
