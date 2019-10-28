#include "Rectangle.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        Rectangle::Rectangle(float x, float y, float width, float height)
        {
          this->x = x;
          this->y = y;
          this->width = width;
          this->height = height;
        }

        Rectangle::Rectangle(const Rectangle& rectangle)
        {
          x = rectangle.x;
          y = rectangle.y;
          width = rectangle.width;
          height = rectangle.height;
        }

        Rectangle& Rectangle::operator=(const Rectangle& rectangle)
        {
          x = rectangle.x;
          y = rectangle.y;
          width = rectangle.width;
          height = rectangle.height;
          return *this;
        }

        bool Rectangle::isInside(float vx, float vy) const
        {
          if(x <= vx && vx <= x + width)
          {
            if(y <= vy && vy <= y + height)
            {
              return true;
            }
          }
          return false;
        }
      }
    }
  }
}
