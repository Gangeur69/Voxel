#ifndef VOXELCHUNKMESH_H
#define VOXELCHUNKMESH_H

#include "VoxelTerrainTexture.h"
#include "../../graphics/Mesh.h"
#include "../../utils/LinkedList.h"

using namespace gt::doubovik::graphics;

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      namespace terrain
      {
        extern const int VERTICIES_PER_FACE;
        extern const float TOP_FACE[];
        extern const float BOTTOM_FACE[];
        extern const float FRONT_FACE[];
        extern const float LEFT_FACE[];
        extern const float RIGHT_FACE[];
        extern const float BACK_FACE[];

        extern const unsigned int FACE_INDICES[];
        extern const int INDICES_PER_FACE;

        class VoxelChunkMesh
        {
        private:
          LinkedList<float> positions;
          LinkedList<float> uvs;
          LinkedList<float> normals;
          LinkedList<unsigned int> indices;
          int vertexAmount = 0;
          int indicesAmount = 0;
          Mesh mesh;

          VoxelChunkMesh(const VoxelChunkMesh&);
          void operator=(const VoxelChunkMesh&);
        public:
          VoxelChunkMesh();
          void addBlockFace(const VoxelTerrainTexture&, int, int, int, int, const float*);
          void loadToGPU();
          void render() const;
        };
      }
    }
  }
}

#endif
