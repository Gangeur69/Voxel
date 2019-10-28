#ifndef PANELTEXTURE_H
#define PANELTEXTURE_H

#include "../graphics/Texture.h"

using namespace gt::doubovik::graphics;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class PanelTexture
      {
      private:
        Texture* background;
        Texture* border;
        Texture* corner;

      public:
        PanelTexture(Texture*, Texture*, Texture*);
        PanelTexture(const PanelTexture&);
        PanelTexture& operator=(const PanelTexture&);

        Texture* getBackground() const;
        Texture* getBorder() const;
        Texture* getCorner() const;
      };
    }
  }
}

#endif
