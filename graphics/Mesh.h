#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include "../utils/LinkedList.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      class Mesh
      {
      private:
        int vertexAmount = 0;
        int indicesAmount = 0;
        GLuint vao;
        LinkedList<GLuint> vbos;

        void genVao();
        GLuint genVbo();
        Mesh(const Mesh&);
        void operator=(const Mesh&);
      public:
        Mesh();
        ~Mesh();

        void deleteData();
        void addVbo(int, int, float*, int);
        void addIVbo(int, int, int*, int);
        void addIndices(unsigned int*, int);
        GLuint getVao() const;
        int getIndicesAmount() const;
        void setVertexAmount(int);
        int getVertexAmount() const;
      };
    }
  }
}

#endif
