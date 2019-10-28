#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include "../utils/String.h"
#include "../utils/LinkedList.h"
#include "../math/Matrix4x4.h"
#include "../math/Vector3.h"

using namespace gt::doubovik;
using namespace gt::doubovik::utils;
using namespace gt::doubovik::math;

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      class Shader
      {
      private:
        GLuint program;
        GLuint vertexShader;
        GLuint fragmentShader;
        LinkedList<GLint> variables;

        Shader(const Shader&);
        void operator=(const Shader&);
        GLuint createShader(const String&, GLenum);
        void checkShaderError(GLuint, GLuint, bool, const char*);
      public:
        Shader(const String&);
        virtual ~Shader();
        void bind();
        void registerVariable(const char*);
        void registerArray(const char*, int);
        void loadVariable(int, const Matrix4x4&);
        void loadVariable(int, const Vector3&);
        void loadVariable(int, float, float, float, float);
        void loadVariable(int, float, float);
        void loadVariable(int, float);
        void loadArray(int, const Matrix4x4*, int);
      };
    }
  }
}

#endif
