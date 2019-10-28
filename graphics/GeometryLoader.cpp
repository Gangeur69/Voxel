#include "GeometryLoader.h"

#include "../libs/stb_image.h"
#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {

      GLuint loadToGPU(float* positions, int positionAmount, float* texCoords, int texCoordAmount)
      {
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        addVBO(0, 3, positions, positionAmount);
        addVBO(1, 2, texCoords, texCoordAmount);

        glBindVertexArray(0);
        return vao;
      }

      GLuint loadToGPU(float* positions, int posAmount, unsigned int* indices, int indAmount)
      {
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        GLuint ibo;
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indAmount, indices, GL_STATIC_DRAW);

        addVBO(0, 3, positions, posAmount);
        glBindVertexArray(0);
        return vao;
      }

      GLuint loadToGPU(float* positions, int amount)
      {
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        addVBO(0, 3, positions, amount);
        glBindVertexArray(0);
        return vao;
      }

      GLuint addVBO(int index, int dimention, float* data, int amount)
      {
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glEnableVertexAttribArray(index);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*amount, data, GL_STATIC_DRAW);
        glVertexAttribPointer(index, dimention, GL_FLOAT, GL_FALSE, 0, 0);
        glDisableVertexAttribArray(index);
        return vbo;
      }

      GLuint adduiVBO(int index, int dimention, int* data, int amount)
      {
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glEnableVertexAttribArray(index);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(int)*amount, data, GL_STATIC_DRAW);
        glVertexAttribIPointer(index, dimention, GL_INT, 0, 0);
        glDisableVertexAttribArray(index);
        return vbo;
      }

      GLuint loadTexture(const char* fileName)
      {
        int width;
        int height;
        int numComponents;
        unsigned char* data = stbi_load(fileName, &width, &height, &numComponents, 4);

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //GL_CLAMP_TO_EDGE //repeat texture when out axe1
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //repeat texture when out axe2

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //image compression pixel calulation
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //image expanssion pixel calulation

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
        return texture;
      }

      GLuint loadFontAtlas(const char* fileName)
      {
        int width;
        int height;
        int numComponents;
        unsigned char* data = stbi_load(fileName, &width, &height, &numComponents, 4);

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);


        glGenerateMipmap(GL_TEXTURE_2D); //gens "lower versions of texture"

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0.0); //quality resolution of mipmaps

        stbi_image_free(data);
        return texture;
      }
    }
  }
}
