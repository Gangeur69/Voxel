#ifndef VOXELRENDERER_H
#define VOXELRENDERER_H

#include <GL/glew.h>
#include <mutex>

#include "../graphics/Shader.h"
#include "../graphics/Camera.h"

#include "../math/Matrix4x4.h"
#include "../math/Vector3.h"
#include "../math/geometry/CollisionData.h"

#include "terrain/VoxelBlock.h"
#include "terrain/VoxelChunk.h"
#include "terrain/VoxelPlanet.h"
#include "terrain/VoxelTerrainTexture.h"
#include "terrain/VoxelChunkSet.h"

#include "../physics/Object.h"

using namespace gt::doubovik::graphics;
using namespace gt::doubovik::math;
using namespace gt::doubovik::math::geometry;
using namespace gt::doubovik::voxel::terrain;
using namespace gt::doubovik::physics;

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class VoxelRenderer
      {
      private:
        Shader shader;
        VoxelTerrainTexture* terrainTexture;
        VoxelChunkSet* chunkSet;
        ChunkGenerator generator;
      public:
        VoxelRenderer(const Matrix4x4&);
        ~VoxelRenderer();
        void render(Camera&, std::mutex&);
        void loadNext(std::mutex&);
        VoxelBlock* getBlock(int, const Vector3&, const Vector3&);
        void breakBlock(int, const Vector3&, const Vector3&);
        void placeBlock(int, const Vector3&, const Vector3&, VoxelMaterial*);
        void checkCollisions(float, Object&);
      };
    }
  }
}

#endif
