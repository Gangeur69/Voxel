#include "CharData.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace text
      {
        CharData::CharData()
        {

        }

        CharData::CharData(int id, float x, float y, float width, float height, float xoffset, float yoffset, float xadvance)
        {
          this->id = id;
          this->x = x;
          this->y = y;
          this->width = width;
          this->height = height;
          this->xoffset = xoffset;
          this->yoffset = yoffset;
          this->xadvance = xadvance;
        }

        CharData::CharData(const CharData& data)
        {
          id = data.id;
          x = data.x;
          y = data.y;
          width = data.width;
          height = data.height;
          xoffset = data.xoffset;
          yoffset = data.yoffset;
          xadvance = data.xadvance;
        }

        CharData& CharData::operator=(const CharData& data)
        {
          id = data.id;
          x = data.x;
          y = data.y;
          width = data.width;
          height = data.height;
          xoffset = data.xoffset;
          yoffset = data.yoffset;
          xadvance = data.xadvance;
          return *this;
        }

        int CharData::getId() const
        {
          return id;
        }

        float CharData::getX() const
        {
          return x;
        }

        float CharData::getY() const
        {
          return y;
        }

        float CharData::getWidth() const
        {
          return width;
        }

        float CharData::getHeight() const
        {
          return height;
        }

        float CharData::getXOffset() const
        {
          return xoffset;
        }

        float CharData::getYOffset() const
        {
          return yoffset;
        }

        float CharData::getXAdvance() const
        {
          return xadvance;
        }
      }
    }
  }
}
