#ifndef GEOMETRYLOADER_H
#define GEOMETRYLOADER_H

#include <GL/glew.h>

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      GLuint loadToGPU(float*, int);
      GLuint loadToGPU(float*, int, unsigned int*, int);
      GLuint loadToGPU(float*, int, float*, int);
      GLuint addVBO(int, int, float*, int);
      GLuint adduiVBO(int, int, int*, int);
      GLuint loadTexture(const char*);
      GLuint loadFontAtlas(const char*);
    }
  }
}

#endif
