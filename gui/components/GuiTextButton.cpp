#include "GuiTextButton.h"

#include "../../utils/String.h"

using namespace gt::doubovik::utils;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace components
      {
        GuiTextButton::GuiTextButton(const char* chars, Font* font, float textSize, bool centered, float width, float height) : GuiButton(), text(String(chars), font, width, textSize, centered)
        {
          this->borderSize = 0.06;
          this->width = width;
          this->height = height;
        }

        GuiTextButton::GuiTextButton(const GuiTextButton& button) : GuiButton(), text(button.text)
        {
          borderSize = button.borderSize;
        }

        GuiTextButton& GuiTextButton::operator=(const GuiTextButton& button)
        {
          GuiButton::operator=(button);
          borderSize = button.borderSize;
          text = button.text;
          return *this;
        }

        void GuiTextButton::onLeftClick()
        {
          GuiButton::onLeftClick();
          std::cout << "BUTTON CLICK" << std::endl;
        }

        void GuiTextButton::render(GuiRenderer* renderer, float parentx, float parenty)
        {
          GuiButton::render(renderer, parentx, parenty);
          Vector3 color(1.0, 1.0, 1.0);
          if(isHovered)
          {
            color*=4.0;
          }
          renderer->renderPanel(borderSize, x + parentx, y + parenty, width, height, color);
          renderer->renderText(x + parentx, y + parenty, text);
        }
      }
    }
  }
}
