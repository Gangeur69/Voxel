#include "ChunkGenerator.h"

#include <iostream>
#include "VoxelMaterial.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      namespace terrain
      {
        ChunkGenerator::ChunkGenerator() : random(435)
        {

        }

        ChunkGenerator::ChunkGenerator(const ChunkGenerator& generator) : random(generator.random)
        {

        }

        ChunkGenerator& ChunkGenerator::operator=(const ChunkGenerator& generator)
        {
          random = generator.random;
          return *this;
        }

        void ChunkGenerator::generate(int chunkX, int chunkY, int chunkZ, VoxelChunk& chunk)
        {
          float cx = (float)(chunkX*CHUNK_SIZE);
          int cy = chunkY*CHUNK_SIZE;
          float cz = (float)(chunkZ*CHUNK_SIZE);
          for(int x=0;x<CHUNK_SIZE;x++)
          {
            for(int z=0;z<CHUNK_SIZE;z++)
            {
              float r = random.getInterpolatedNoise((cx + ((float)x))/20.0, (cz + ((float)z))/20.0);
              int h = 30 + (int)((60.0 - 30.0)*r);
              for(int y=0;y<CHUNK_SIZE;y++)
              {
                if(y + cy < h)
                {
                  chunk.getBlock(x, y, z).setMaterial(&MATERIAL_GRASS);
                }
              }
            }
          }
        }
      }
    }
  }
}
