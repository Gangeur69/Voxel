#include "TextBuilderCursor.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace text
      {
        TextBuilderCursor::TextBuilderCursor()
        {
          x = 0.0;
          y = 0.0;
        }

        TextBuilderCursor::TextBuilderCursor(const TextBuilderCursor& cursor)
        {
          x = cursor.x;
          y = cursor.y;
        }

        TextBuilderCursor& TextBuilderCursor::operator=(const TextBuilderCursor& cursor)
        {
          x = cursor.x;
          y = cursor.y;
          return *this;
        }
      }
    }
  }
}
