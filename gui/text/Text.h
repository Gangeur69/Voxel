#ifndef TEXT_H
#define TEXT_H

#include "../../utils/String.h"
#include "../../graphics/Mesh.h"
#include "Font.h"
#include "../../math/Vector3.h"

using namespace gt::doubovik::utils;
using namespace gt::doubovik::math;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace text
      {
        class Text
        {
        private:
          String data;
          Mesh mesh;
          Font* font;

          float maxLineSize;
          float size;

          bool centered;

          void updateMesh();

        public:
          Vector3 color;

          Text(const String&, Font*, float, float, bool);
          Text(const Text&);
          Text& operator=(const Text&);

          float getSize() const;
          Font* getFont() const;
          float getWidth() const;
          float getHeight() const;
          const Mesh& getMesh() const;
          const String& getData() const;
        };
      }
    }
  }
}

#endif
