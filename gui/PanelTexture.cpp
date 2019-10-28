#include "PanelTexture.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      PanelTexture::PanelTexture(Texture* background, Texture* border, Texture* corner)
      {
        this->background = background;
        this->border = border;
        this->corner = corner;
      }

      PanelTexture::PanelTexture(const PanelTexture& texture)
      {
        background = texture.background;
        border = texture.border;
        corner = texture.corner;
      }

      PanelTexture& PanelTexture::operator=(const PanelTexture& texture)
      {
        background = texture.background;
        border = texture.border;
        corner = texture.corner;
        return *this;
      }

      Texture* PanelTexture::getBackground() const
      {
        return background;
      }

      Texture* PanelTexture::getBorder() const
      {
        return border;
      }

      Texture* PanelTexture::getCorner() const
      {
        return corner;
      }
    }
  }
}
