#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H

#include "VoxelChunk.h"
#include "../../math/RandomGenerator.h"

using namespace gt::doubovik::math;

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      namespace terrain
      {
        class ChunkGenerator
        {
        private:
          RandomGenerator random;
        public:
          ChunkGenerator();
          ChunkGenerator(const ChunkGenerator&);
          ChunkGenerator& operator=(const ChunkGenerator&);
          void generate(int, int, int, VoxelChunk&);
        };
      }
    }
  }
}

#endif
