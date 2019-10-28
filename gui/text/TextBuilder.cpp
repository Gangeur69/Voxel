#include "TextBuilder.h"

#include "CharData.h"
#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace text
      {
        TextBuilder::TextBuilder(char* text, Font* font, float maxLineSize, bool centered)
        {
          this->font = font;
          this->maxLineSize = maxLineSize;
          this->centered = centered;

          int amount = 0;
          while(*(text + amount)  != '\0')
          {
            amount++;
          }
          amount++;

          this->text = new char[amount];
          for(int i=0;i<amount;i++)
          {
            *(this->text + i) = *(text + i);
          }
        }

        TextBuilder::~TextBuilder()
        {
          delete[] text;
        }

        TextBuilder::TextBuilder(const TextBuilder& builder)
        {
          font = builder.font;
          maxLineSize = builder.maxLineSize;
          cursor = builder.cursor;
          centered = builder.centered;

          int amount = 0;
          while(*(builder.text + amount)  != '\0')
          {
            amount++;
          }
          amount++;

          text = new char[amount];
          for(int i=0;i<amount;i++)
          {
            *(text + i) = *(builder.text + i);
          }
        }

        TextBuilder& TextBuilder::operator=(const TextBuilder& builder)
        {
          delete[] text;

          font = builder.font;
          maxLineSize = builder.maxLineSize;
          cursor = builder.cursor;
          centered = builder.centered;

          int amount = 0;
          while(*(builder.text + amount)  != '\0')
          {
            amount++;
          }
          amount++;

          text = new char[amount];
          for(int i=0;i<amount;i++)
          {
            *(text + i) = *(builder.text + i);
          }
          return *this;
        }


        void TextBuilder::getNextWord(String* word, float* size)
        {
          char c = *(text + index);
          *size = 0.0;
          while(c != '\0' && isprint(c) && c != ' ')
          {
            word->addChar(c);
            (*size)+=font->getCharData(c).getXAdvance();
            index++;
            c = *(text + index);
          }
        }

        void TextBuilder::getNextSpaces(String* spaces, float* size)
        {
          char c = *(text + index);
          *size = 0.0;
          while(c != '\0' && c == ' ')
          {
            spaces->addChar(c);
            (*size)+=font->getCharData(c).getXAdvance();
            index++;
            c = *(text + index);
          }
        }

        void TextBuilder::buildChar(char c)
        {
          const CharData data = font->getCharData(c);

          float x = cursor.x + data.getXOffset();
          float y = cursor.y - data.getYOffset();
          cursor.x += data.getXAdvance();

          if(data.getWidth() == 0.0 || data.getHeight() == 0.0)
          {
            return;
          }

          int size = positions.size()/2;

          positions.add(x);
          positions.add(y);

          positions.add(x);
          positions.add(y - data.getHeight());

          positions.add(x + data.getWidth());
          positions.add(y - data.getHeight());

          positions.add(x + data.getWidth());
          positions.add(y);

          uvs.add(data.getX());
          uvs.add(data.getY());

          uvs.add(data.getX());
          uvs.add(data.getY() + data.getHeight());

          uvs.add(data.getX() + data.getWidth());
          uvs.add(data.getY() + data.getHeight());

          uvs.add(data.getX() + data.getWidth());
          uvs.add(data.getY());

          indices.add(size);
          indices.add(size + 1);
          indices.add(size + 2);
          indices.add(size + 2);
          indices.add(size + 3);
          indices.add(size);
        }

        void TextBuilder::buildLine()
        {
          if(centered)
          {
            cursor.x = (maxLineSize - lineSize)/2.0;
          }
          for(LinkedListIterator<char> itt = line.getIterator(); itt.isValid(); itt.next())
          {
            char c = itt.getElement();
            buildChar(c);
          }

          line = String("");
          lineSize = 0.0;

          spaces = String("");
          spacesSize = 0.0;

          cursor.x = 0.0;
          cursor.y -= font->getLineHeight();
        }

        void TextBuilder::buildWord()
        {
          String word;
          float wordSize;
          getNextWord(&word, &wordSize);
          if(lineSize + wordSize + spacesSize > maxLineSize)
          {
            buildLine();
            line = word;
            lineSize = wordSize;
          }
          else
          {
            line+=spaces;
            line+=word;
            lineSize+= spacesSize + wordSize;

            spaces = String("");
            spacesSize = 0.0;
          }
        }

        void TextBuilder::buildSpaces()
        {
          getNextSpaces(&spaces, &spacesSize);
        }

        void TextBuilder::buildSpecialChars()
        {
          char c = *(text + index);
          while(!isprint(c))
          {
            if(c == '\n')
            {
              buildLine();
            }
            index++;
            c = *(text + index);
          }
        }

        void TextBuilder::buildNext()
        {
          char c = *(text + index);
          if(c == '\0')
          {
            return;
          }

          if(isprint(c) && c != ' ')
          {
            buildWord();
          }
          else if(c == ' ')
          {
            buildSpaces();
          }
          else
          {
            buildSpecialChars();
          }
        }

        void TextBuilder::buildLines()
        {
          line = String("");
          lineSize = 0.0;
          index = 0;

          spaces = String("");
          spacesSize = 0.0;

          while(*(text + index) != '\0')
          {
            buildNext();
          }
          if(!line.isEmpty())
          {
            buildLine();
          }
        }

        void TextBuilder::build(Mesh* mesh)
        {

          buildLines();

          int psize = positions.size();
          int isize = indices.size();

          float* apositions = new float[psize];
          float* auvs = new float[psize];
          unsigned int* aindices = new unsigned int[isize];

          positions.toArray(apositions);
          uvs.toArray(auvs);
          indices.toArray(aindices);

          mesh->deleteData();
          mesh->addVbo(0, 2, apositions, psize);
          mesh->addVbo(1, 2, auvs, psize);
          mesh->addIndices(aindices, isize);

          delete[] apositions;
          delete[] auvs;
          delete[] aindices;

          positions.clear();
          uvs.clear();
          indices.clear();
        }
      }
    }
  }
}
