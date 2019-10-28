#include "FontReader.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace text
      {
        FontReader::FontReader(const char* fileName)
        {
          imgx = 512;
          imgy = 512;


          String data = fileToString(fileName);
          LinkedListIterator<char> itt = data.getIterator();
          readNextInfo(itt);
        }

        FontReader::~FontReader()
        {
          delete[] charDatas;
        }

        FontReader::FontReader(const FontReader& reader)
        {
          imgx = reader.imgx;
          imgy = reader.imgy;

          lineHeight = reader.lineHeight;
          amount = reader.amount;

          charDatas = new CharData[amount];
          for(int i=0;i<amount;i++)
          {
            *(charDatas + i) = *(reader.charDatas + i);
          }
        }

        FontReader& FontReader::operator=(const FontReader& reader)
        {
          delete[] charDatas;

          imgx = reader.imgx;
          imgy = reader.imgy;

          lineHeight = reader.lineHeight;
          amount = reader.amount;

          charDatas = new CharData[amount];
          for(int i=0;i<amount;i++)
          {
            *(charDatas + i) = *(reader.charDatas + i);
          }
          return *this;
        }

        void FontReader::skipToText(LinkedListIterator<char>& itt)
        {
          while(itt.isValid() && (!isprint(itt.getElement()) || itt.getElement() == ' '))
          {
            itt.next();
          }
        }

        String FontReader::readNext(LinkedListIterator<char>& itt)
        {
          skipToText(itt);
          String data;
          while(itt.isValid() && isprint(itt.getElement()) && itt.getElement() != ' ')
          {
            data.addChar(itt.getElement());
            itt.next();
          }
          return data;
        }

        void FontReader::readCommun(LinkedListIterator<char>& itt)
        {
          while(itt.isValid())
          {
            String text = readNext(itt);

            if(text == String("page"))
            {
              break;
            }

            LinkedList<String> data = text.split("=");

            String name = data.get(0);
            String value = data.get(1);
            if(name == String("lineHeight"))
            {
              lineHeight = (float)value/(float)imgy;
            }
          }

          readPage(itt);
        }

        void FontReader::readPage(LinkedListIterator<char>& itt)
        {
          while(itt.isValid())
          {
            String text = readNext(itt);

            if(text == String("chars"))
            {
              readChars(itt);
              break;
            }

            LinkedList<String> data = text.split("=");

            String name = data.get(0);
            String value = data.get(1);
            name.print();
            value.print();
          }
        }

        void FontReader::readChars(LinkedListIterator<char>& itt)
        {
          int count;

          while(itt.isValid())
          {
            String text = readNext(itt);

            if(text == String("char"))
            {
              break;
            }

            LinkedList<String> data = text.split("=");

            String name = data.get(0);
            String value = data.get(1);
            if(name == String("count"))
            {
              count = value;
            }
          }

          amount = count + 1;
          charDatas = new CharData[amount];
          int i=0;
          readChar(itt, i);
        }

        void FontReader::readChar(LinkedListIterator<char>& itt, int i)
        {
          int id;

          float x;
          float y;

          float width;
          float height;

          float xoffset;
          float yoffset;

          float xadvance;

          while(itt.isValid())
          {
            String text = readNext(itt);

            if(text.isEmpty())
            {
              break;
            }

            if(text == String("char"))
            {
              break;
            }

            LinkedList<String> data = text.split("=");

            String name = data.get(0);
            String value = data.get(1);
            if(name == String("id"))
            {
              id = value;
            }
            else if(name == String("x"))
            {
              x = (float)value/(float)imgx;
            }
            else if(name == String("y"))
            {
              y = (float)value/(float)imgy;
            }
            else if(name == String("width"))
            {
              width = (float)value/(float)imgx;
            }
            else if(name == String("height"))
            {
              height = (float)value/(float)imgy;
            }
            else if(name == String("xoffset"))
            {
              xoffset = (float)value/(float)imgx;
            }
            else if(name == String("yoffset"))
            {
              yoffset = (float)value/(float)imgy;
            }
            else if(name == String("xadvance"))
            {
              xadvance = (float)value/(float)imgx;
            }
          }
          std::cout << "x: " << x << std::endl;
          CharData charData(id, x, y, width, height, xoffset, yoffset, xadvance);
          *(charDatas + i) = charData;
          i++;
          if(itt.isValid())
          {
            readChar(itt, i);
          }
        }

        void FontReader::readNextInfo(LinkedListIterator<char>& itt)
        {
          String flag = readNext(itt);
          flag.print();

          if(flag == String("common"))
          {
            readCommun(itt);
          }
        }

        float FontReader::getLineHeight() const
        {
          return lineHeight;
        }

        int FontReader::getAmount() const
        {
          return amount;
        }

        CharData* FontReader::getCharDatas() const
        {
          return charDatas;
        }
      }
    }
  }
}
