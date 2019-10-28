#ifndef TEXTBUILDERCURSOR_H
#define TEXTBUILDERCURSOR_H

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace text
      {
        class TextBuilderCursor
        {
        public:
          float x;
          float y;

          TextBuilderCursor();
          TextBuilderCursor(const TextBuilderCursor&);
          TextBuilderCursor& operator=(const TextBuilderCursor&);
        };
      }
    }
  }
}

#endif
