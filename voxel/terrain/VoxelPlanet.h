#ifndef VOXELPLANET_H
#define VOXELPLANET_H

#include "VoxelChunk.h"

#include "../../utils/ArrayList.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      namespace terrain
      {
        class VoxelPlanet
        {
        private:
          ArrayList<ArrayList<ArrayList<VoxelChunk>>> chunks;
          int getListIndex(int);
          void setChunk(int, int, int, const VoxelChunk&);
          void initializeListTo(int, int, int);
        public:
          VoxelPlanet();
          VoxelChunk& getChunk(int, int, int);
        };
      }
    }
  }
}

#endif
