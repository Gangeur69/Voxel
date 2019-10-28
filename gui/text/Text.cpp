#include "Text.h"

#include "TextBuilder.h"
#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace text
      {
        void Text::updateMesh()
        {
          int amount = data.size();
          char* chars = new char[amount+1];
          data.toChars(chars);
          *(chars + amount) = '\0';
          TextBuilder builder(chars, font, maxLineSize/size, centered);
          builder.build(&mesh);
          delete[] chars;
        }

        Text::Text(const String& data, Font* font, float maxLineSize, float size, bool centered)
        {
          this->data = data;
          this->font = font;
          this->maxLineSize = maxLineSize;
          this->size = size;
          this->centered = centered;
          updateMesh();
        }

        Text::Text(const Text& text)
        {
          data = text.data;
          font = text.font;
          maxLineSize = text.maxLineSize;
          size = text.size;
          centered = text.centered;
          updateMesh();
        }

        Text& Text::operator=(const Text& text)
        {
          data = text.data;
          font = text.font;
          maxLineSize = text.maxLineSize;
          size = text.size;
          centered = text.centered;
          updateMesh();
          return *this;
        }

        float Text::getSize() const
        {
          return size;
        }

        Font* Text::getFont() const
        {
          return font;
        }

        float Text::getWidth() const
        {
          return maxLineSize;
        }

        float Text::getHeight() const
        {
          return font->getLineHeight()*size;
        }

        const Mesh& Text::getMesh() const
        {
          return mesh;
        }

        const String& Text::getData() const
        {
          return data;
        }
      }
    }
  }
}
