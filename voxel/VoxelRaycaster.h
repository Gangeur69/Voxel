#ifndef VOXELRAYCASTER_H
#define VOXELRAYCASTER_H

#include "../math/Vector3.h"

using namespace gt::doubovik::math;

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class VoxelRaycaster
      {
      private:
        int max;

        int x;
        int y;
        int z;

        bool useX;
        bool useY;
        bool useZ;

        int stepX;
        int stepY;
        int stepZ;

        float tx;
        float ty;
        float tz;

        float nextX;
        float nextY;
        float nextZ;

        void calculateParameters(int, float, float, int*, float*, float*, bool*);
      public:
        VoxelRaycaster(int, const Vector3&, const Vector3&);
        VoxelRaycaster(const VoxelRaycaster&);
        VoxelRaycaster& operator=(const VoxelRaycaster&);

        void next();
        void next(int*, int, float*, float);
        void next(int* x, int* y, int stepX, int stepY, float* tx, float* ty, float nextX, float nextY);
        void next(int*, int*, int*, int, int, int, float*, float*, float*, float, float, float);

        bool isValid() const;
        int getX() const;
        int getY() const;
        int getZ() const;
      };
    }
  }
}

#endif
