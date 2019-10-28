#include "VoxelMaterial.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      namespace terrain
      {
        VoxelMaterial MATERIAL_AIR(0, 0, 0, false);
        VoxelMaterial MATERIAL_GRASS(0, 2, 1, true);

        VoxelMaterial::VoxelMaterial(int topFaceTextureId, int bottomFaceTextureId, int sideFaceTextureId, bool visible)
        {
          this->topFaceTextureId = topFaceTextureId;
          this->bottomFaceTextureId = bottomFaceTextureId;
          this->sideFaceTextureId = sideFaceTextureId;
          this->visible = visible;
        }

        VoxelMaterial::VoxelMaterial(const VoxelMaterial& material)
        {
          topFaceTextureId = material.topFaceTextureId;
          bottomFaceTextureId = material.bottomFaceTextureId;
          sideFaceTextureId = material.sideFaceTextureId;
          visible = material.visible;
        }

        VoxelMaterial& VoxelMaterial::operator=(const VoxelMaterial& material)
        {
          topFaceTextureId = material.topFaceTextureId;
          bottomFaceTextureId = material.bottomFaceTextureId;
          sideFaceTextureId = material.sideFaceTextureId;
          visible = material.visible;
          return *this;
        }

        int VoxelMaterial::getTopFaceTextureId() const
        {
          return topFaceTextureId;
        }

        int VoxelMaterial::getBottomFaceTextureId() const
        {
          return bottomFaceTextureId;
        }

        int VoxelMaterial::getSideFaceTextureId() const
        {
          return sideFaceTextureId;
        }

        bool VoxelMaterial::isVisible() const
        {
          return visible;
        }
      }
    }
  }
}
