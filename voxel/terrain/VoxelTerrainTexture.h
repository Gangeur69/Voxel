#ifndef VOXELTERRAINTEXTURE_H
#define VOXELTERRAINTEXTURE_H

#include <GL/glew.h>

#include "../../utils/LinkedList.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      namespace terrain
      {
        class VoxelTerrainTexture
        {
        private:
          int sizeX;
          int sizeY;
          GLuint texture;
          float faceSizeX;
          float faceSizeY;
          VoxelTerrainTexture(const VoxelTerrainTexture&);
          void operator=(const VoxelTerrainTexture&);
        public:
          VoxelTerrainTexture(int, int, GLuint);
          ~VoxelTerrainTexture();
          GLuint getTexture() const;
          void getTextureCoords(int, LinkedList<float>&) const;
        };
      }
    }
  }
}

#endif
