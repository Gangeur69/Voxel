#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      class Texture
      {
      private:
        GLuint id;

        Texture(const Texture&);
        void operator=(const Texture&);
      public:
        Texture(GLuint);
        ~Texture();

        GLuint getId() const;
      };
    }
  }
}

#endif
