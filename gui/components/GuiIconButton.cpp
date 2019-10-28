#include "GuiIconButton.h"

#include "../../math/Vector3.h"
#include <iostream>

using namespace gt::doubovik::math;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace components
      {
        GuiIconButton::GuiIconButton(Texture* texture, bool* isVisible, float width, float height) : GuiButton()
        {
          this->texture = texture;
          this->width = width;
          this->height = height;
          this->isVisible = isVisible;
        }

        GuiIconButton::GuiIconButton(const GuiIconButton& button) : GuiButton(button)
        {
          texture = button.texture;
        }

        GuiIconButton& GuiIconButton::operator=(const GuiIconButton& button)
        {
          GuiButton::operator=(button);
          texture = button.texture;
          return *this;
        }

        void GuiIconButton::onLeftClick()
        {
          GuiButton::onLeftClick();
          if(*isVisible)
          {
            *isVisible = false;
          }
          else
          {
            *isVisible = true;
          }
        }

        void GuiIconButton::render(GuiRenderer* renderer, float parentx, float parenty)
        {
          GuiButton::render(renderer, parentx, parenty);
          Vector3 color(1.0, 1.0, 1.0);
          if(isHovered)
          {
            color*=4.0;
          }

          renderer->renderQuad(texture, parentx + x, parenty + y, width, height, color);
        }
      }
    }
  }
}
