#include "Texture.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      Texture::Texture(GLuint id)
      {
        this->id = id;
      }

      Texture::~Texture()
      {
        glDeleteTextures(1, &id);
      }

      Texture::Texture(const Texture&)
      {

      }

      void Texture::operator=(const Texture&)
      {

      }

      GLuint Texture::getId() const
      {
        return id;
      }
    }
  }
}
