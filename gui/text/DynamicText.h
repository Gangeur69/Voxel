#ifndef DYNAMICTEXT_H
#define DYNAMICTEXT_H

#include "Text.h"
#include "Font.h"
#include "../../math/Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace text
      {
        class DynamicText
        {
        private:
          Font* font;
          float maxLineSize;
          float size;
          bool centered;
          Vector3 color;

          Text* text;

          void deleteText();
        public:
          DynamicText(Font*, float, float, bool);
          DynamicText(Font*, float, bool);
          ~DynamicText();
          DynamicText(const DynamicText&);
          DynamicText& operator=(const DynamicText&);

          void setText(const String&);
          void setText(const String&, float);
          Text* getText() const;
          float getHeight() const;
          void clear();
          void setColor(float, float, float);
        };
      }
    }
  }
}

#endif
