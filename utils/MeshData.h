#ifndef MESHDATA_H
#define MESHDATA_H

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class MeshData
      {
      private:
        int vertexAmount;
        int indicesAmount;
        float* positions;
        float* texCoords;
        float* normals;
        unsigned int* indices;
        int* indexedData;
      public:
        MeshData(int, int, float*, float*, float*, unsigned int*, int*);
        ~MeshData();
        MeshData(const MeshData&);
        MeshData& operator=(const MeshData&);
        int getVertexAmount() const;
        int getIndicesAmount() const;
        float* getPositions() const;
        float* getTextureCoords() const;
        float* getNormals() const;
        unsigned int* getIndices() const;
        int* getIndexedData() const;
      };
    }
  }
}

#endif
