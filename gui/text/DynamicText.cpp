#include "DynamicText.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace text
      {
        DynamicText::DynamicText(Font* font, float maxLineSize, float size, bool centered)
        {
          this->font = font;
          this->maxLineSize = maxLineSize;
          this->size = size;
          this->centered = centered;

          text = NULL;
        }

        DynamicText::DynamicText(Font* font, float size, bool centered)
        {
          this->font = font;
          this->size = size;
          this->centered = centered;
          maxLineSize = 1.0;

          text = NULL;
        }

        DynamicText::~DynamicText()
        {
          deleteText();
        }

        DynamicText::DynamicText(const DynamicText& dynamicText)
        {
          font = dynamicText.font;
          maxLineSize = dynamicText.maxLineSize;
          size = dynamicText.size;
          centered = dynamicText.centered;
          color = dynamicText.color;

          if(dynamicText.text != NULL)
          {
            text = new Text(*dynamicText.text);
          }
          else
          {
            text = NULL;
          }
        }

        DynamicText& DynamicText::operator=(const DynamicText& dynamicText)
        {
          font = dynamicText.font;
          maxLineSize = dynamicText.maxLineSize;
          size = dynamicText.size;
          centered = dynamicText.centered;
          color = dynamicText.color;

          deleteText();
          if(dynamicText.text != NULL)
          {
            text = new Text(*dynamicText.text);
          }
          else
          {
            text = NULL;
          }
          return *this;
        }

        void DynamicText::deleteText()
        {
          if(text != NULL)
          {
            delete text;
            text = NULL;
          }
        }

        void DynamicText::clear()
        {
          deleteText();
        }

        void DynamicText::setText(const String& data)
        {
          if(text != NULL)
          {
            if(data == text->getData())
            {
              return;
            }
          }
          deleteText();
          text = new Text(data, font, maxLineSize, size, centered);
          text->color = color;
        }

        void DynamicText::setText(const String& data, float maxLineSize)
        {
          this->maxLineSize = maxLineSize;
          setText(data);
        }

        Text* DynamicText::getText() const
        {
          return text;
        }

        float DynamicText::getHeight() const
        {
          if(text == NULL)
          {
            return 0;
          }
          return text->getHeight();
        }

        void DynamicText::setColor(float r, float g, float b)
        {
          color = Vector3(r, g, b);
          if(text != NULL)
          {
            text->color = color;
          }
        }
      }
    }
  }
}
