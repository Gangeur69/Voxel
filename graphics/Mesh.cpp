#include "Mesh.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      Mesh::Mesh()
      {
        vao = 0;
      }

      Mesh::~Mesh()
      {
        deleteData();
      }

      Mesh::Mesh(const Mesh& m)
      {
        //private
      }

      void Mesh::operator=(const Mesh& m)
      {
        //private
      }

      void Mesh::deleteData()
      {
        if(vao != 0)
        {
          glDeleteVertexArrays(1, &vao);
        }
        for(LinkedListIterator<GLuint> itt=vbos.getIterator();itt.isValid();itt.next())
        {
          glDeleteBuffers(1, &itt.getElement());
        }
        vbos.clear();
        vao = 0;
        indicesAmount = 0;
      }

      void Mesh::genVao()
      {
        if(vao == 0)
        {
          glGenVertexArrays(1, &vao);
        }
      }

      GLuint Mesh::genVbo()
      {
        GLuint vbo;
        glGenBuffers(1, &vbo);
        vbos.add(vbo);
        return vbo;
      }

      void Mesh::addIVbo(int index, int dimention, int* data, int amount)
      {
        genVao();
        glBindVertexArray(vao);
        GLuint vbo = genVbo();
        glEnableVertexAttribArray(index);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(int)*amount, data, GL_STATIC_DRAW);
        glVertexAttribIPointer(index, dimention, GL_INT, 0, 0);
        glDisableVertexAttribArray(index);
        glBindVertexArray(0);
      }

      void Mesh::addVbo(int index, int dimention, float* data, int amount)
      {
        genVao();
        glBindVertexArray(vao);
        GLuint vbo = genVbo();
        glEnableVertexAttribArray(index);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*amount, data, GL_STATIC_DRAW);
        glVertexAttribPointer(index, dimention, GL_FLOAT, GL_FALSE, 0, 0);
        glDisableVertexAttribArray(index);
        glBindVertexArray(0);
      }

      void Mesh::addIndices(unsigned int* indices, int amount)
      {
        indicesAmount = amount;
        genVao();
        glBindVertexArray(vao);
        GLuint vbo = genVbo();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*amount, indices, GL_STATIC_DRAW);
        glBindVertexArray(0);
      }

      GLuint Mesh::getVao() const
      {
        return vao;
      }

      int Mesh::getIndicesAmount() const
      {
        return indicesAmount;
      }

      void Mesh::setVertexAmount(int vertexAmount)
      {
        this->vertexAmount = vertexAmount;
      }

      int Mesh::getVertexAmount() const
      {
        return vertexAmount;
      }
    }
  }
}
