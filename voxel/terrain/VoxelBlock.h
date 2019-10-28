#ifndef VOXELBLOCK_H
#define VOXELBLOCK_H

#include "VoxelMaterial.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      namespace terrain
      {
        class VoxelBlock
        {
        private:
          VoxelMaterial* material;
        public:
          VoxelBlock();
          VoxelBlock& operator=(const VoxelBlock&);
          const VoxelMaterial& getMaterial() const;
          void setMaterial(VoxelMaterial*);
        };
      }
    }
  }
}

#endif
