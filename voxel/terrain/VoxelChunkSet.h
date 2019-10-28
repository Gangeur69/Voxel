#ifndef VOXELCHUNKSET_H
#define VOXELCHUNKSET_H

#include <mutex>

#include "VoxelChunk.h"
#include "VoxelTerrainTexture.h"
#include "ChunkGenerator.h"
#include "../../math/Vector3i.h"
#include "../../math/Vector3.h"
#include "../../math/Matrix4x4.h"
#include "../../math/Quaternion.h"
#include "../../utils/LinkedList.h"

#include "../../physics/Object.h"

#include "../../math/geometry/ConvexShape.h"
#include "../../math/geometry/CollisionData.h"

using namespace gt::doubovik::math;
using namespace gt::doubovik::math::geometry;
using namespace gt::doubovik::physics;

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      namespace terrain
      {
        extern ConvexShape cubeShape;
        class VoxelChunkSet
        {
        private:
          int width;
          int height;
          VoxelChunk** chunks;
          Vector3i position;
          LinkedList<VoxelChunk*> toUnload;

          int getIndex(int, int, int) const;
          VoxelChunk*& chunkAt(int, int, int) const;
          VoxelChunk* uchunkAt(int, int, int) const;
          Vector3i getChunkPosition(Vector3i&, int, int, int);
          Vector3i getSetPosition(Vector3i&, int, int, int);
        public:
          VoxelChunkSet(int, int, Vector3i&);
          ~VoxelChunkSet();
          VoxelChunkSet(const VoxelChunkSet&);
          VoxelChunkSet& operator=(const VoxelChunkSet&);

          int getWidth() const;
          int getHeight() const;
          bool isInSet(Vector3i&, int, int, int);
          VoxelChunk* getChunk(int, int, int);
          bool loadNextInColumn(ChunkGenerator&, int, int);
          void loadNext(ChunkGenerator&);
          bool surroundingsLoaded(int, int, int);
          bool buildNextMeshInColumn(const VoxelTerrainTexture&, int, int);
          void buildNextMesh(const VoxelTerrainTexture&);
          bool loadNextMeshInColumnToGpu(int, int);
          void loadNextMeshToGpu();
          void render();
          void updateChunkPosition(Vector3i&);
          void updatePosition(const Vector3&);

          void getBlockAndChunk(int x, int y, int z, VoxelBlock**, VoxelChunk**);
          VoxelBlock* getBlock(int x, int y, int z);
          VoxelBlock* getBlock(int, const Vector3&, const Vector3&);
          VoxelBlock* getBlockBefore(int max, const Vector3& start, const Vector3& direction);
          void placeBlock(int, const Vector3&, const Vector3&, VoxelMaterial*);
          void breakBlock(int, const Vector3&, const Vector3&);
          void reloadChunkAfterModification(int, int, int, VoxelChunk*);

          void checkCollisions(float, Object&);

          void getCollisionData(const Vector3&, float, Object&, float*, Vector3*);
          void getCollisionDataAt(const Vector3&, float, Object&, int, int, int, const Matrix4x4&, const Matrix4x4&, float, float*, Vector3*);

        };
      }
    }
  }
}

#endif
