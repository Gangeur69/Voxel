#ifndef VOXELCHUNK_H
#define VOXELCHUNK_H

#include "VoxelBlock.h"
#include "VoxelChunkMesh.h"
#include "VoxelTerrainTexture.h"
#include "../../utils/LinkedList.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      namespace terrain
      {
        extern const int CHUNK_SIZE;

        class VoxelChunk
        {
        private:
          VoxelBlock* blocks;
          VoxelChunkMesh mesh;
          bool meshBuilt;
          bool meshLoaded;
          VoxelBlock& blockAt(int, int, int) const;
        public:
          VoxelChunk();
          ~VoxelChunk();
          VoxelChunk(const VoxelChunk&);
          VoxelChunk& operator=(const VoxelChunk&);
          VoxelBlock& getBlock(int, int, int);
          void render() const;
          bool hasMeshBuilt() const;
          bool hasMeshLoaded() const;
          void loadToGPU();
          void reload();
          bool faceIsVisible(int, int, int, int, VoxelChunk*, VoxelChunk*, VoxelChunk*, VoxelChunk*, VoxelChunk*, VoxelChunk*) const;
          void updateMesh(const VoxelTerrainTexture&, int, int, int, VoxelChunk*, VoxelChunk*, VoxelChunk*, VoxelChunk*, VoxelChunk*, VoxelChunk*);
        };
      }
    }
  }
}

#endif
