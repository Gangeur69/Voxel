#include "Font.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace text
      {
        Font::Font(float lineHeight, int amount, CharData* charDatas, Texture* atlas)
        {
          this->lineHeight = lineHeight;
          this->amount = amount;
          this->atlas = atlas;

          this->charDatas = new CharData[amount];
          for(int i=0;i<amount;i++)
          {
            *(this->charDatas + i) = *(charDatas + i);
          }
        }

        Font::~Font()
        {
          delete[] charDatas;
        }

        Font::Font(const Font& font)
        {
          lineHeight = font.lineHeight;
          amount = font.amount;
          atlas = font.atlas;

          charDatas = new CharData[amount];
          for(int i=0;i<amount;i++)
          {
            *(charDatas + i) = *(font.charDatas + i);
          }
        }

        Font& Font::operator=(const Font& font)
        {
          delete[] charDatas;

          lineHeight = font.lineHeight;
          amount = font.amount;
          atlas = font.atlas;

          charDatas = new CharData[amount];
          for(int i=0;i<amount;i++)
          {
            *(charDatas + i) = *(font.charDatas + i);
          }
          return *this;
        }

        const CharData& Font::getCharData(char c) const
        {
          int asciicode = int(c);
          for(int i=0;i<amount;i++)
          {
            if((*(charDatas + i)).getId() == asciicode)
            {
              return *(charDatas + i);
            }
          }
          throw("ascii does not exist");
          return *charDatas;
        }

        float Font::getLineHeight() const
        {
          return lineHeight;
        }

        Texture* Font::getAtlas() const
        {
          return atlas;
        }
      }
    }
  }
}
