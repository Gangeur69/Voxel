#include "Quaternion.h"

#include <math.h>
#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      Quaternion::Quaternion()
      {
        a = 0;
        b = 0;
        c = 0;
        d = 0;
      }

      Quaternion::Quaternion(float a, float b, float c, float d)
      {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
      }

      Quaternion::Quaternion(const Matrix4x4& m)
      {
        float k;
        if(m.get(2,2) < 0)
        {
          if(m.get(0,0) > m.get(1,1))
          {
            a = m.get(2,1) - m.get(1,2);
            b = 1 + m.get(0,0) - m.get(1,1) - m.get(2,2);
            c = m.get(0,1) + m.get(1,0);
            d = m.get(0,2) + m.get(2,0);
            k = b;
          }
          else
          {
            a = m.get(0,2) - m.get(2,0);
            b = m.get(0,1) + m.get(1,0);
            c = 1 -m.get(0,0) + m.get(1,1) - m.get(2,2);
            d = m.get(1,2) + m.get(2,1);
            k = c;
          }
        }
        else
        {
          if(m.get(0,0) < -m.get(1,1))
          {
            a = m.get(1,0) - m.get(0,1);
            b = m.get(0,2) + m.get(2,0);
            c = m.get(1,2) + m.get(2,1);
            d = 1 - m.get(0,0) - m.get(1,1) + m.get(2,2);
            k = d;
          }
          else
          {
            a = 1 + m.get(0,0) + m.get(1,1) + m.get(2,2);
            b = m.get(2,1) - m.get(1,2);
            c = m.get(0,2) - m.get(2,0);
            d = m.get(1,0) - m.get(0,1);
            k = a;
          }
        }

        k = 0.5/sqrt(k);
        a*=k;
        b*=k;
        c*=k;
        d*=k;
      }

      Quaternion::Quaternion(const Vector3& v)
      {
        a = 0;
        b = v.getX();
        c = v.getY();
        d = v.getZ();
      }

      Quaternion::Quaternion(float angle, const Vector3& v)
      {
        angle*=(M_PI/180);
        angle/=2;
        a = cos(angle);
        float coef = sin(angle);
        b = coef*v.getX();
        c = coef*v.getY();
        d = coef*v.getZ();
      }

      Quaternion::Quaternion(const Quaternion& q)
      {
        a = q.a;
        b = q.b;
        c = q.c;
        d = q.d;
      }

      Quaternion& Quaternion::operator=(const Quaternion& q)
      {
        a = q.a;
        b = q.b;
        c = q.c;
        d = q.d;
        return *this;
      }

      float& Quaternion::getA()
      {
        return a;
      }

      float& Quaternion::getB()
      {
        return b;
      }

      float& Quaternion::getC()
      {
        return c;
      }

      float& Quaternion::getD()
      {
        return d;
      }

      Quaternion Quaternion::conjugate() const
      {
        return Quaternion(a, -b, -c, -d);
      }

      Quaternion Quaternion::sq(const Quaternion& q) const
      {
        return (*this)*q*(*this).conjugate();
      }

      Vector3 Quaternion::rotate(const Vector3& v) const
      {
        Quaternion rotres = sq(Quaternion(v));
        return Vector3(rotres.getB(), rotres.getC(), rotres.getD());
      }

      Matrix3x3 Quaternion::toMatrix3x3() const
      {
        float a2 = a*a;
        float b2 = b*b;
        float c2 = c*c;
        float d2 = d*d;

        float ad2 = 2*a*d;
        float bc2 = 2*b*c;
        float bd2 = 2*b*d;
        float ac2 = 2*a*c;
        float ab2 = 2*a*b;
        float cd2 = 2*c*d;

        Matrix3x3 m;
        m.get(0,0) = a2 + b2 - c2 - d2;
        m.get(1,0) = ad2 + bc2;
        m.get(2,0) = bd2 - ac2;

        m.get(0,1) = bc2 - ad2;
        m.get(1,1) = a2 - b2 + c2 - d2;
        m.get(2,1) = ab2 + cd2;

        m.get(0,2) = ac2 + bd2;
        m.get(1,2) = cd2 - ab2;
        m.get(2,2) = a2 - b2 - c2 + d2;
        return m;
      }

      Matrix4x4 Quaternion::toMatrix4x4() const
      {
        float a2 = a*a;
        float b2 = b*b;
        float c2 = c*c;
        float d2 = d*d;

        float ad2 = 2*a*d;
        float bc2 = 2*b*c;
        float bd2 = 2*b*d;
        float ac2 = 2*a*c;
        float ab2 = 2*a*b;
        float cd2 = 2*c*d;

        Matrix4x4 m;
        m.get(0,0) = a2 + b2 - c2 - d2;
        m.get(1,0) = ad2 + bc2;
        m.get(2,0) = bd2 - ac2;

        m.get(0,1) = bc2 - ad2;
        m.get(1,1) = a2 - b2 + c2 - d2;
        m.get(2,1) = ab2 + cd2;

        m.get(0,2) = ac2 + bd2;
        m.get(1,2) = cd2 - ab2;
        m.get(2,2) = a2 - b2 - c2 + d2;
        return m;
      }

      float Quaternion::dot(const Quaternion& q) const
      {
        return a*q.a + b*q.b + c*q.c + d*q.d;
      }

      Quaternion Quaternion::slerp(float t, const Quaternion& q2) const
      {
        float dotp = dot(q2);
        Quaternion v1 = *this;
        Quaternion v2 = q2;
        if(dotp < 0.0)
        {
          v2 = -v2;
          dotp = -dotp;
        }

        const double DOT_THRESHOLD = 0.9995;
        if (dotp > DOT_THRESHOLD) {

          Quaternion v1mv2 = (v2 - v1);

          Quaternion result = v1 + t*v1mv2;
          float resLen = sqrt(result.dot(result));
          if(resLen != 0)
          {
            result*=1.0/resLen;
          }
          return result;
        }

        float theta = acos(dotp);
        float sinTheta = sin(theta);

        float thetat = t*theta;
        float sinThetat = sin(thetat);

        float s1 = cos(thetat) - dotp * (sinThetat / sinTheta);
        float s2 = sinThetat / sinTheta;

        return (s1 * v1) + (s2 * v2);
      }

      Quaternion Quaternion::operator+(const Quaternion& q) const
      {
        return Quaternion(a + q.a, b + q.b, c + q.c, d + q.d);
      }

      Quaternion Quaternion::operator-(const Quaternion& q) const
      {
        return Quaternion(a - q.a, b - q.b, c - q.c, d - q.d);
      }

      Quaternion Quaternion::operator*(const Quaternion& q) const
      {
        float ares = a*q.a - b*q.b - c*q.c - d*q.d;
        float bres = a*q.b + b*q.a + c*q.d - d*q.c;
        float cres = a*q.c + c*q.a - b*q.d + d*q.b;
        float dres = d*q.a + a*q.d + b*q.c - c*q.b;
        return Quaternion(ares, bres, cres, dres);
      }

      Quaternion Quaternion::operator-() const
      {
        return Quaternion(-a,-b,-c,-d);
      }

      void Quaternion::operator*=(float x)
      {
        a*=x;
        b*=x;
        c*=x;
        d*=x;
      }

      Quaternion operator*(Quaternion& q, float x)
      {
        float a = x * q.getA();
        float b = x * q.getB();
        float c = x * q.getC();
        float d = x * q.getD();
        return Quaternion(a, b, c, d);
      }

      Quaternion operator*(float x, Quaternion& q)
      {
        return q*x;
      }
    }
  }
}
