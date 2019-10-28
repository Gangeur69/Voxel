#include "VoxelTerrainTexture.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      namespace terrain
      {

        VoxelTerrainTexture::VoxelTerrainTexture(int sizeX, int sizeY, GLuint texture)
        {
          this->sizeX = sizeX;
          this->sizeY = sizeY;
          this->texture = texture;
          this->faceSizeX = 1.0/((float)sizeX);
          this->faceSizeY = 1.0/((float)sizeY);
        }
        VoxelTerrainTexture::~VoxelTerrainTexture()
        {
          glDeleteTextures(1, &texture);
        }

        VoxelTerrainTexture::VoxelTerrainTexture(const VoxelTerrainTexture&)
        {
          //private
        }

        void VoxelTerrainTexture::operator=(const VoxelTerrainTexture&)
        {
          //private
        }

        GLuint VoxelTerrainTexture::getTexture() const
        {
          return texture;
        }

        void VoxelTerrainTexture::getTextureCoords(int id, LinkedList<float>& texCoords) const
        {
          int xAmount = id%sizeX;
          int yAmount = (id - xAmount)/sizeX;

          float xAdd = ((float)xAmount)/((float)sizeX);
          float yAdd = ((float)yAmount)/((float)sizeY);

          texCoords.add(xAdd);
          texCoords.add(yAdd + faceSizeY);

          texCoords.add(xAdd + faceSizeX);
          texCoords.add(yAdd + faceSizeY);

          texCoords.add(xAdd + faceSizeX);
          texCoords.add(yAdd);

          texCoords.add(xAdd);
          texCoords.add(yAdd);
        }
      }
    }
  }
}
