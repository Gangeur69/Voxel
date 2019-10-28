#include "VoxelRaycaster.h"

#include "VoxelManager.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      VoxelRaycaster::VoxelRaycaster(int max, const Vector3& start, const Vector3& direction)
      {
        this->max = max;

        floatCoordsToInt(start.getX(), start.getY(), start.getZ(), &x, &y, &z);
        calculateParameters(x, start.getX(), direction.getX(), &stepX, &tx, &nextX, &useX);
        calculateParameters(y, start.getY(), direction.getY(), &stepY, &ty, &nextY, &useY);
        calculateParameters(z, start.getZ(), direction.getZ(), &stepZ, &tz, &nextZ, &useZ);
      }

      VoxelRaycaster::VoxelRaycaster(const VoxelRaycaster& raycaster)
      {
        max = raycaster.max;
        x = raycaster.x;
        y = raycaster.y;
        z = raycaster.z;
        useX = raycaster.useX;
        useY = raycaster.useY;
        useZ = raycaster.useZ;
        stepX = raycaster.stepX;
        stepY = raycaster.stepY;
        stepZ = raycaster.stepZ;
        tx = raycaster.tx;
        ty = raycaster.ty;
        tz = raycaster.tz;
        nextX = raycaster.nextX;
        nextY = raycaster.nextY;
        nextZ = raycaster.nextZ;
      }

      VoxelRaycaster& VoxelRaycaster::operator=(const VoxelRaycaster& raycaster)
      {
        max = raycaster.max;
        x = raycaster.x;
        y = raycaster.y;
        z = raycaster.z;
        useX = raycaster.useX;
        useY = raycaster.useY;
        useZ = raycaster.useZ;
        stepX = raycaster.stepX;
        stepY = raycaster.stepY;
        stepZ = raycaster.stepZ;
        tx = raycaster.tx;
        ty = raycaster.ty;
        tz = raycaster.tz;
        nextX = raycaster.nextX;
        nextY = raycaster.nextY;
        nextZ = raycaster.nextZ;
        return *this;
      }

      void VoxelRaycaster::calculateParameters(int x, float startx, float directionx, int* stepX, float* tx, float* nextX, bool* useX)
      {
        if(directionx*directionx < 0.000001)
        {
          *useX = false;
          return;
        }

        *useX = true;
        if(directionx > 0.0)
        {
          *stepX = 1;
          *tx = (((float)(x + 1)) - startx)/directionx;
          *nextX = 1.0/directionx;
        }
        else
        {
          *stepX = -1;
          *tx = (((float)x) - startx)/directionx;
          *nextX = -1.0/directionx;
        }
      }

      void VoxelRaycaster::next()
      {
        max--;
        if(max < 0)
        {
          max = 0;
        }

        if(!useX)
        {
          if(!useY)
          {
            next(&z, stepZ, &tz, nextZ);
          }
          else
          {
            next(&y, &z, stepY, stepZ, &ty, &tz, nextY, nextZ);
          }
        }
        else if(!useY)
        {
          if(!useZ)
          {
            next(&x, stepX, &tx, nextX);
          }
          else
          {
            next(&x, &z, stepX, stepZ, &tx, &tz, nextX, nextZ);
          }
        }
        else if(!useZ)
        {
          next(&x, &y, stepX, stepY, &tx, &ty, nextX, nextY);
        }
        else
        {
          next(&x, &y, &z, stepX, stepY, stepZ, &tx, &ty, &tz, nextX, nextY, nextZ);
        }
      }

      void VoxelRaycaster::next(int* x, int stepX, float* tx, float nextX)
      {
        (*tx)+=nextX;
        (*x)+=stepX;
      }

      void VoxelRaycaster::next(int* x, int* y, int stepX, int stepY, float* tx, float* ty, float nextX, float nextY)
      {
        if(*tx < *ty)
        {
          (*tx)+=nextX;
          (*x)+=stepX;
        }
        else
        {
          (*ty)+=nextX;
          (*y)+=stepY;
        }
      }

      void VoxelRaycaster::next(int* x, int* y, int* z, int stepX, int stepY, int stepZ, float* tx, float* ty, float* tz, float nextX, float nextY, float nextZ)
      {
        if(*tx < *ty && *tx < *tz)
        {
          (*tx)+=nextX;
          (*x)+=stepX;
        }
        else if(*ty < *tz)
        {
          (*ty)+=nextY;
          (*y)+=stepY;
        }
        else
        {
          (*tz)+=nextZ;
          (*z)+=stepZ;
        }
      }

      bool VoxelRaycaster::isValid() const
      {
        return max > 0;
      }

      int VoxelRaycaster::getX() const
      {
        return x;
      }

      int VoxelRaycaster::getY() const
      {
        return y;
      }

      int VoxelRaycaster::getZ() const
      {
        return z;
      }
    }
  }
}
