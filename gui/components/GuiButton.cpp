#include "GuiButton.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace components
      {
        GuiButton::GuiButton() : GuiComponent()
        {

        }

        GuiButton::GuiButton(const GuiButton& button) : GuiComponent(button)
        {

        }

        GuiButton& GuiButton::operator=(const GuiButton& button)
        {
          GuiComponent::operator=(button);
          return *this;
        }

        void GuiButton::onLeftClick()
        {
          GuiComponent::onLeftClick();
        }

        void GuiButton::render(GuiRenderer* renderer, float parentx, float parenty)
        {
          GuiComponent::render(renderer, parentx, parenty);
        }
      }
    }
  }
}
