#ifndef FONT_H
#define FONT_H

#include "CharData.h"
#include "../../utils/String.h"
#include "../../graphics/Texture.h"

using namespace gt::doubovik::utils;
using namespace gt::doubovik::graphics;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace text
      {
        class Font
        {
        private:
          float lineHeight;
          CharData* charDatas;
          int amount;
          Texture* atlas;
        public:
          Font(float, int, CharData*, Texture*);
          ~Font();
          Font(const Font&);
          Font& operator=(const Font&);

          const CharData& getCharData(char) const;
          float getLineHeight() const;
          Texture* getAtlas() const;
        };
      }
    }
  }
}

#endif
