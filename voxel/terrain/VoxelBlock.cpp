#include "VoxelBlock.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      namespace terrain
      {
        VoxelBlock::VoxelBlock()
        {
          material = &MATERIAL_AIR;
        }

        VoxelBlock& VoxelBlock::operator=(const VoxelBlock& block)
        {
          material = block.material;
          return *this;
        }

        const VoxelMaterial& VoxelBlock::getMaterial() const
        {
          return *material;
        }

        void VoxelBlock::setMaterial(VoxelMaterial* material)
        {
          this->material = material;
        }
      }
    }
  }
}
