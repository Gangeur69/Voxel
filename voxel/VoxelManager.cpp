#include "VoxelManager.h"

#include "terrain/VoxelChunk.h"

using namespace gt::doubovik::voxel::terrain;

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      void floatCoordToInt(float x, int* ix) //ok
      {
        *ix = (int)x;
        if(x < 0.0)
        {
          (*ix)--;
        }
      }

      void floatCoordsToInt(float x, float y, float z, int* ix, int* iy, int* iz) //ok
      {
        floatCoordToInt(x, ix);
        floatCoordToInt(y, iy);
        floatCoordToInt(z, iz);
      }

      void floatCoordToChunkCoord(float x, int* ix)
      {
        *ix = (int)(x/CHUNK_SIZE);
        if(x < 0.0)
        {
          (*ix)--;
        }
      }

      void floatCoordsToChunkCoords(float x, float y, float z, int* ix, int* iy, int* iz)
      {
        floatCoordToChunkCoord(x, ix);
        floatCoordToChunkCoord(y, iy);
        floatCoordToChunkCoord(z, iz);
      }

      void floatCoordToLocalChunkCoord(float x, int* ix)
      {
        *ix = (int)x;
        floatCoordToInt(x, ix);
        intCoordToLocalChunkCoord(*ix, ix);
      }

      void floatCoordsToLocalChunkCoords(float x, float y, float z, int* ix, int* iy, int* iz)
      {
        floatCoordToLocalChunkCoord(x, ix);
        floatCoordToLocalChunkCoord(y, iy);
        floatCoordToLocalChunkCoord(z, iz);
      }

      void intCoordToChunkCoord(int x, int* ix) //ok
      {
        if(x >= 0)
        {
          *ix = (int)(x/CHUNK_SIZE);
        }
        else
        {
          *ix = (int)((x + 1)/CHUNK_SIZE) -1;
        }
      }

      void intCoordsToChunkCoords(int x, int y, int z, int* ix, int* iy, int* iz) //ok
      {
        intCoordToChunkCoord(x, ix);
        intCoordToChunkCoord(y, iy);
        intCoordToChunkCoord(z, iz);
      }

      void intCoordToLocalChunkCoord(int x, int* ix) //ok p
      {
        if(x >= 0)
        {
          *ix = x%CHUNK_SIZE;
        }
        else
        {
          *ix = (x + 1)%CHUNK_SIZE -1;
          *ix = CHUNK_SIZE + *ix;
        }
      }

      void intCoordsToLocalChunkCoords(int x, int y, int z, int* ix, int* iy, int* iz) //ok
      {
        intCoordToLocalChunkCoord(x, ix);
        intCoordToLocalChunkCoord(y, iy);
        intCoordToLocalChunkCoord(z, iz);
      }
    }
  }
}
