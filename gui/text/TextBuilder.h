#ifndef TEXTBUILDER_H
#define TEXTBUILDER_H

#include "Font.h"
#include "TextBuilderCursor.h"
#include "../../graphics/Mesh.h"
#include "../../utils/LinkedList.h"
#include "../../utils/String.h"

using namespace gt::doubovik::graphics;
using namespace gt::doubovik::utils;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace text
      {
        class TextBuilder
        {
        private:
          char* text;
          Font* font;
          float maxLineSize;
          bool centered;

          String line;
          float lineSize;

          String spaces;
          float spacesSize;

          int index;
          TextBuilderCursor cursor;

          LinkedList<float> positions;
          LinkedList<float> uvs;
          LinkedList<unsigned int> indices;

          void getNextWord(String*, float*);
          void getNextSpaces(String*, float*);
          void buildChar(char);
          void buildLine();
          void buildLines();
          void buildWord();
          void buildSpaces();
          void buildSpecialChars();
          void buildNext();
        public:
          TextBuilder(char*, Font*, float, bool);
          ~TextBuilder();
          TextBuilder(const TextBuilder&);
          TextBuilder& operator=(const TextBuilder&);

          void build(Mesh*);
        };
      }
    }
  }
}

#endif
