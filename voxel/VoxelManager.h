#ifndef VOXELMANAGER_H
#define VOXELMANAGER_H

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      void floatCoordToInt(float, int*);
      void floatCoordsToInt(float, float, float, int*, int*, int*);
      void floatCoordToChunkCoord(float , int*);
      void floatCoordsToChunkCoords(float, float, float, int*, int*, int*);
      void floatCoordToLocalChunkCoord(float, int*);
      void floatCoordsToLocalChunkCoords(float, float, float, int*, int*, int*);

      void intCoordToChunkCoord(int, int*);
      void intCoordsToChunkCoords(int, int, int, int*, int*, int*);
      void intCoordToLocalChunkCoord(int, int*);
      void intCoordsToLocalChunkCoords(int, int, int, int*, int*, int*);
    }
  }
}

#endif
