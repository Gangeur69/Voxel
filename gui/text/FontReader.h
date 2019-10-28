#ifndef FONTREADER_H
#define FONTREADER_H

#include "../../utils/String.h"
#include "../../utils/LinkedList.h"
#include "CharData.h"

using namespace gt::doubovik::utils;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace text
      {
        class FontReader
        {
        private:
          int imgx;
          int imgy;

          float lineHeight;

          int amount;
          CharData* charDatas;

          void skipToText(LinkedListIterator<char>& itt);
          String readNext(LinkedListIterator<char>& itt);
          void readCommun(LinkedListIterator<char>& itt);
          void readPage(LinkedListIterator<char>& itt);
          void readChars(LinkedListIterator<char>& itt);
          void readChar(LinkedListIterator<char>& itt, int);
          void readNextInfo(LinkedListIterator<char>& itt);
        public:
          FontReader(const char*);
          ~FontReader();
          FontReader(const FontReader&);
          FontReader& operator=(const FontReader&);

          float getLineHeight() const;
          int getAmount() const;
          CharData* getCharDatas() const;
        };
      }
    }
  }
}

#endif
