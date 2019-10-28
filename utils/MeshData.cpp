#include "MeshData.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      MeshData::MeshData(int vertexAmount, int indicesAmount, float* positions, float* texCoords, float* normals, unsigned int* indices, int* indexedData)
      {
        this->vertexAmount = vertexAmount;
        this->indicesAmount = indicesAmount;

        this->positions = new float[vertexAmount*3];
        this->texCoords = new float[vertexAmount*2];
        this->normals = new float[vertexAmount*3];
        this->indexedData = new int[vertexAmount*3];

        for(int i=0;i<vertexAmount*3;i++)
        {
          *(this->positions + i) = *(positions + i);
          *(this->normals + i) = *(normals + i);
          *(this->indexedData + i) = *(indexedData + i);
        }

        for(int i=0;i<vertexAmount*2;i++)
        {
          *(this->texCoords + i) = *(texCoords + i);
        }

        this->indices = new unsigned int[indicesAmount];
        for(int i=0;i<indicesAmount;i++)
        {
          *(this->indices + i) = *(indices + i);
        }
      }

      MeshData::~MeshData()
      {
        delete [] positions;
        delete [] texCoords;
        delete [] normals;
        delete [] indices;
        delete [] indexedData;
      }

      MeshData::MeshData(const MeshData& meshData)
      {
        vertexAmount = meshData.vertexAmount;
        indicesAmount = meshData.indicesAmount;

        positions = new float[vertexAmount*3];
        texCoords = new float[vertexAmount*2];
        normals = new float[vertexAmount*3];
        indexedData = new int[vertexAmount*3];

        for(int i=0;i<vertexAmount*3;i++)
        {
          *(positions + i) = *(meshData.positions + i);
          *(normals + i) = *(meshData.normals + i);
          *(indexedData + i) = *(meshData.indexedData + i);
        }
        for(int i=0;i<vertexAmount*2;i++)
        {
          *(texCoords + i) = *(meshData.texCoords + i);
        }

        indices = new unsigned int[indicesAmount];
        for(int i=0;i<indicesAmount;i++)
        {
          *(indices + i) = *(meshData.indices + i);
        }
      }

      MeshData& MeshData::operator=(const MeshData& meshData)
      {
        delete [] positions;
        delete [] texCoords;
        delete [] normals;
        delete [] indices;
        delete [] indexedData;

        vertexAmount = meshData.vertexAmount;
        indicesAmount = meshData.indicesAmount;

        positions = new float[vertexAmount*3];
        texCoords = new float[vertexAmount*2];
        normals = new float[vertexAmount*3];
        indexedData = new int[vertexAmount*3];

        for(int i=0;i<vertexAmount*3;i++)
        {
          *(positions + i) = *(meshData.positions + i);
          *(normals + i) = *(meshData.normals + i);
          *(indexedData + i) = *(meshData.indexedData + i);
        }
        for(int i=0;i<vertexAmount*2;i++)
        {
          *(texCoords + i) = *(meshData.texCoords + i);
        }

        indices = new unsigned int[indicesAmount];
        for(int i=0;i<indicesAmount;i++)
        {
          *(indices + i) = *(meshData.indices + i);
        }
        return *this;
      }

      int MeshData::getVertexAmount() const
      {
        return vertexAmount;
      }

      int MeshData::getIndicesAmount() const
      {
        return indicesAmount;
      }

      float* MeshData::getPositions() const
      {
        return positions;
      }

      float* MeshData::getTextureCoords() const
      {
        return texCoords;
      }

      float* MeshData::getNormals() const
      {
        return normals;
      }

      unsigned int* MeshData::getIndices() const
      {
        return indices;
      }

      int* MeshData::getIndexedData() const
      {
        return indexedData;
      }
    }
  }
}
