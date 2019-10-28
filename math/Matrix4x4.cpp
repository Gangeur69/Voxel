#include "Matrix4x4.h"

#include <math.h>

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      Matrix4x4::Matrix4x4() : SquareMatrix(4)
      {

      }

      Matrix4x4::Matrix4x4(int swidth, int sheight, float angleX, float angleY, float zN, float zF) : SquareMatrix(4)
      {
        float ratio = ((float)sheight)/((float)swidth);
        float acoef = (M_PI/180);
        acoef/=2;
        angleX*=acoef;
        angleY*=acoef;
        get(0,0) = ratio/tan(angleX);
        get(1,1) = 1/tan(angleY);
        get(2,2) = (zN + zF)/(zN - zF);
        get(2,3) = (2*zN*zF)/(zN - zF);
        get(3,2) = -1;
        get(3,3) = 0;
      }

      Vector3 Matrix4x4::operator*(const Vector3& v) const
      {
        float x = get(0,0)*v.getX() + get(0,1)*v.getY() + get(0,2)*v.getZ() + get(0,3);
        float y = get(1,0)*v.getX() + get(1,1)*v.getY() + get(1,2)*v.getZ() + get(1,3);
        float z = get(2,0)*v.getX() + get(2,1)*v.getY() + get(2,2)*v.getZ() + get(2,3);
        return Vector3(x,y,z);
      }

      Vector3 Matrix4x4::getScale() const
      {
        float x = Vector3(get(0,0), get(1,0), get(2,0)).getLength();
        float y = Vector3(get(0,1), get(1,1), get(2,1)).getLength();
        float z = Vector3(get(0,2), get(1,2), get(2,2)).getLength();
        return Vector3(x, y, z);
      }

      void Matrix4x4::unScale()
      {
        Vector3 scale = getScale();
        if(scale.getX() != 0)
        {
          float k = 1.0/scale.getX();
          get(0,0)*=k;
          get(1,0)*=k;
          get(2,0)*=k;
        }
        if(scale.getY() != 0)
        {
          float k = 1.0/scale.getY();
          get(0,1)*=k;
          get(1,1)*=k;
          get(2,1)*=k;
        }
        if(scale.getZ() != 0)
        {
          float k = 1.0/scale.getZ();
          get(0,2)*=k;
          get(1,2)*=k;
          get(2,2)*=k;
        }
      }

      Matrix4x4 Matrix4x4::operator*(const Matrix4x4& matrix) const
      {
        Matrix4x4 prod;
        for(unsigned int i=0;i<prod.height;i++)
        {
          for(unsigned int j=0;j<prod.width;j++)
          {
            prod.get(i,j) = lineColumnProduct(i, j, matrix);
          }
        }
        return prod;
      }
    }
  }
}
