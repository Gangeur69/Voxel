#include "VoxelChunk.h"

#include <iostream>
#include <stdlib.h>

#include "VoxelMaterial.h"

#include "../../graphics/GeometryLoader.h"

using namespace gt::doubovik::graphics;

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      namespace terrain
      {
        const int CHUNK_SIZE = 16;

        VoxelChunk::VoxelChunk()
        {
          meshBuilt = false;
          meshLoaded = false;
          blocks = new VoxelBlock[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE];
        }

        VoxelChunk::~VoxelChunk()
        {
          delete [] blocks;
        }

        VoxelChunk::VoxelChunk(const VoxelChunk& chunk)
        {
          meshBuilt = false;
          blocks = new VoxelBlock[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE];
          for(int i=0;i<CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE;i++)
          {
            *(blocks + i) = *(chunk.blocks + i);
          }
        }

        VoxelChunk& VoxelChunk::operator=(const VoxelChunk& chunk)
        {
          delete [] blocks;
          meshBuilt = false;
          blocks = new VoxelBlock[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE];
          for(int i=0;i<CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE;i++)
          {
            *(blocks + i) = *(chunk.blocks + i);
          }
          return *this;
        }

        VoxelBlock& VoxelChunk::blockAt(int x, int y, int z) const
        {
          int i = x + CHUNK_SIZE*y + CHUNK_SIZE*CHUNK_SIZE*z;
          return *(blocks + i);
        }

        void VoxelChunk::render() const
        {
          mesh.render();
        }

        bool VoxelChunk::hasMeshBuilt() const
        {
          return meshBuilt;
        }

        bool VoxelChunk::hasMeshLoaded() const
        {
          return meshLoaded;
        }

        void VoxelChunk::loadToGPU()
        {
          mesh.loadToGPU();
          meshLoaded = true;
        }

        void VoxelChunk::reload()
        {
          meshBuilt = false;
          meshLoaded = false;
        }

        VoxelBlock& VoxelChunk::getBlock(int x, int y, int z)
        {
          if(x >= CHUNK_SIZE)
          {
            std::cerr << "ERROR index x: " << x << " is out of chunk bounds!" << std::endl;
            exit(EXIT_FAILURE);
          }
          if(y >= CHUNK_SIZE)
          {
            std::cerr << "ERROR index y: " << y << " is out of chunk bounds!" << std::endl;
            exit(EXIT_FAILURE);
          }
          if(z >= CHUNK_SIZE)
          {
            std::cerr << "ERROR index z: " << z << " is out of chunk bounds!" << std::endl;
            exit(EXIT_FAILURE);
          }
          return blockAt(x, y, z);
        }

        bool VoxelChunk::faceIsVisible(int faceId, int x, int y, int z, VoxelChunk* up, VoxelChunk* down, VoxelChunk* front, VoxelChunk* left, VoxelChunk* right, VoxelChunk* back) const
        {
          if(faceId == 0) //TOP_FACE
          {
            y++;
            if(y >= CHUNK_SIZE)
            {
              if(up != NULL)
              {
                return !up->blockAt(x, 0, z).getMaterial().isVisible();
              }
              else
              {
                return true;
              }
            }
          }
          else if(faceId == 1) //BOTTOM_FACE
          {
            y--;
            if(y < 0)
            {
              if(down != NULL)
              {
                return !down->blockAt(x, CHUNK_SIZE-1, z).getMaterial().isVisible();
              }
              else
              {
                return true;
              }
            }
          }
          else if(faceId == 2) //FRONT_FACE
          {
            z--;
            if(z < 0)
            {
              if(front != NULL)
              {
                return !front->blockAt(x, y, CHUNK_SIZE-1).getMaterial().isVisible();
              }
              else
              {
                return true;
              }
            }
          }
          else if(faceId == 3) //LEFT_FACE
          {
            x--;
            if(x < 0)
            {
              if(left != NULL)
              {
                return !left->blockAt(CHUNK_SIZE-1, y, z).getMaterial().isVisible();
              }
              else
              {
                return true;
              }
            }
          }
          else if(faceId == 4) //RIGHT_FACE
          {
            x++;
            if(x >= CHUNK_SIZE)
            {
              if(right != NULL)
              {
                return !right->blockAt(0, y, z).getMaterial().isVisible();
              }
              else
              {
                return true;
              }
            }
          }
          else if(faceId == 5) //BACK_FACE
          {
            z++;
            if(z >= CHUNK_SIZE)
            {
              if(back != NULL)
              {
                return !back->blockAt(x, y, 0).getMaterial().isVisible();
              }
              else
              {
                return true;
              }
            }
          }

          return !blockAt(x, y, z).getMaterial().isVisible();
        }

        void VoxelChunk::updateMesh(const VoxelTerrainTexture& terranTexture, int chunkX, int chunkY, int chunkZ, VoxelChunk* up, VoxelChunk* down, VoxelChunk* front, VoxelChunk* left, VoxelChunk* right, VoxelChunk* back)
        {
          for(int x=0;x<CHUNK_SIZE;x++)
          {
            for(int y=0;y<CHUNK_SIZE;y++)
            {
              for(int z=0;z<CHUNK_SIZE;z++)
              {
                VoxelBlock& block = blockAt(x, y, z);
                if(block.getMaterial().isVisible())
                {
                  int totalX = x + chunkX*CHUNK_SIZE;
                  int totalY = y + chunkY*CHUNK_SIZE;
                  int totalZ = z + chunkZ*CHUNK_SIZE;
                  if(faceIsVisible(0, x, y , z, up, down, front, left, right, back))
                  {
                    mesh.addBlockFace(terranTexture, block.getMaterial().getTopFaceTextureId(), totalX, totalY, totalZ, TOP_FACE);
                  }
                  if(faceIsVisible(1, x, y , z, up, down, front, left, right, back))
                  {
                    mesh.addBlockFace(terranTexture, block.getMaterial().getBottomFaceTextureId(), totalX, totalY, totalZ, BOTTOM_FACE);
                  }
                  if(faceIsVisible(2, x, y , z, up, down, front, left, right, back))
                  {
                    mesh.addBlockFace(terranTexture, block.getMaterial().getSideFaceTextureId(), totalX, totalY, totalZ, FRONT_FACE);
                  }
                  if(faceIsVisible(3, x, y , z, up, down, front, left, right, back))
                  {
                    mesh.addBlockFace(terranTexture, block.getMaterial().getSideFaceTextureId(), totalX, totalY, totalZ, LEFT_FACE);
                  }
                  if(faceIsVisible(4, x, y , z, up, down, front, left, right, back))
                  {
                    mesh.addBlockFace(terranTexture, block.getMaterial().getSideFaceTextureId(), totalX, totalY, totalZ, RIGHT_FACE);
                  }
                  if(faceIsVisible(5, x, y , z, up, down, front, left, right, back))
                  {
                    mesh.addBlockFace(terranTexture, block.getMaterial().getSideFaceTextureId(), totalX, totalY, totalZ, BACK_FACE);
                  }
                }
              }
            }
          }
          meshBuilt = true;
        }
      }
    }
  }
}
