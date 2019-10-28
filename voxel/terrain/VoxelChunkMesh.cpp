#include "VoxelChunkMesh.h"

#include <GL/glew.h>

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      namespace terrain
      {

        const int VERTICIES_PER_FACE = 4;
        const float TOP_FACE[] = {0,1,0, 1,1,0, 1,1,1, 0,1,1};
        const float BOTTOM_FACE[] = {0,0,1, 1,0,1, 1,0,0, 0,0,0};
        const float FRONT_FACE[] = {0,0,0, 1,0,0, 1,1,0, 0,1,0};
        const float LEFT_FACE[] = {0,0,1, 0,0,0, 0,1,0, 0,1,1};
        const float RIGHT_FACE[] = {1,0,0, 1,0,1, 1,1,1, 1,1,0};
        const float BACK_FACE[] = {1,0,1, 0,0,1, 0,1,1, 1,1,1};

        const unsigned int FACE_INDICES[] = {2,1,0,0,3,2};
        const int INDICES_PER_FACE = 6;

        VoxelChunkMesh::VoxelChunkMesh()
        {

        }

        VoxelChunkMesh::VoxelChunkMesh(const VoxelChunkMesh&)
        {
          //private
        }

        void VoxelChunkMesh::operator=(const VoxelChunkMesh&)
        {
          //private
        }

        void VoxelChunkMesh::addBlockFace(const VoxelTerrainTexture& terrainTexture, int faceTextureId, int x, int y, int z, const float* face)
        {
          for(int i=0;i<VERTICIES_PER_FACE;i++)
          {
            positions.add(*(face + 3*i) + x);
            positions.add(*(face + 3*i + 1) + y);
            positions.add(*(face + 3*i + 2) + z);

            if(face == TOP_FACE)
            {
              normals.add(0.0);
              normals.add(1.0);
              normals.add(0.0);
            }
            else if(face == BOTTOM_FACE)
            {
              normals.add(0.0);
              normals.add(-1.0);
              normals.add(0.0);
            }
            else if(face == FRONT_FACE)
            {
              normals.add(0.0);
              normals.add(0.0);
              normals.add(-1.0);
            }
            else if(face == BACK_FACE)
            {
              normals.add(0.0);
              normals.add(0.0);
              normals.add(1.0);
            }
            else if(face == LEFT_FACE)
            {
              normals.add(-1.0);
              normals.add(0.0);
              normals.add(0.0);
            }
            else if(face == RIGHT_FACE)
            {
              normals.add(1.0);
              normals.add(0.0);
              normals.add(0.0);
            }

          }

          for(int i=0;i<INDICES_PER_FACE;i++)
          {
            indices.add(vertexAmount + *(FACE_INDICES + i));
          }
          vertexAmount+=VERTICIES_PER_FACE;
          indicesAmount+=INDICES_PER_FACE;

          terrainTexture.getTextureCoords(faceTextureId, uvs);
        }

        void VoxelChunkMesh::loadToGPU()
        {
          if(vertexAmount > 0 && indicesAmount > 0)
          {
            float* positionsArray = new float[vertexAmount*3];
            float* uvsArray = new float[vertexAmount*2];
            float* normalsArray = new float[vertexAmount*3];
            unsigned int* indicesArray = new unsigned int[indicesAmount];

            positions.toArray(positionsArray);
            uvs.toArray(uvsArray);
            normals.toArray(normalsArray);
            indices.toArray(indicesArray);

            mesh.deleteData();

            mesh.addVbo(0, 3, positionsArray, vertexAmount*3);
            mesh.addVbo(1, 2, uvsArray, vertexAmount*2);
            mesh.addVbo(2, 3, normalsArray, vertexAmount*3);
            mesh.addIndices(indicesArray, indicesAmount);

            delete [] positionsArray;
            delete [] uvsArray;
            delete [] normalsArray;
            delete [] indicesArray;
          }

          positions.clear();
          uvs.clear();
          normals.clear();
          indices.clear();

          vertexAmount = 0;
          indicesAmount = 0;
        }

        void VoxelChunkMesh::render() const
        {
          if(mesh.getVao() != 0)
          {
            glBindVertexArray(mesh.getVao());
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);

            glDrawElements(GL_TRIANGLES, mesh.getIndicesAmount(), GL_UNSIGNED_INT, 0);

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(2);
            glBindVertexArray(0);
          }
        }
      }
    }
  }
}
