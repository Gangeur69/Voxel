#ifndef VECTOR3I_H
#define VECTOR3I_H

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      class Vector3i
      {
      private:
        int x;
        int y;
        int z;
      public:
        Vector3i(int, int, int);
        Vector3i(const Vector3i&);
        Vector3i& operator=(const Vector3i&);
        int& getX();
        int& getY();
        int& getZ();
      };
    }
  }
}

#endif
