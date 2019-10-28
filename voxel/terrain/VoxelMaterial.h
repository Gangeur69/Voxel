#ifndef VOXELMATERIAL_H
#define VOXELMATERIAL_H

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      namespace terrain
      {
        class VoxelMaterial
        {
        private:
          int topFaceTextureId;
          int bottomFaceTextureId;
          int sideFaceTextureId;
          bool visible;
        public:
          VoxelMaterial(int, int, int, bool);
          VoxelMaterial(const VoxelMaterial&);
          VoxelMaterial& operator=(const VoxelMaterial&);
          int getTopFaceTextureId() const;
          int getBottomFaceTextureId() const;
          int getSideFaceTextureId() const;
          bool isVisible() const;
        };

        extern VoxelMaterial MATERIAL_AIR;
        extern VoxelMaterial MATERIAL_GRASS;
      }
    }
  }
}

#endif
