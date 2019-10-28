#ifndef CHARDATA_H
#define CHARDATA_H

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace text
      {
        class CharData
        {
        private:
          int id;
          float x;
          float y;
          float width;
          float height;
          float xoffset;
          float yoffset;
          float xadvance;
        public:
          CharData();
          CharData(int, float, float, float, float, float, float, float);
          CharData(const CharData&);
          CharData& operator=(const CharData&);

          int getId() const;
          float getX() const;
          float getY() const;
          float getWidth() const;
          float getHeight() const;
          float getXOffset() const;
          float getYOffset() const;
          float getXAdvance() const;
        };
      }
    }
  }
}

#endif
