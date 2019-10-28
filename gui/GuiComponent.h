#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

#include "GuiRenderer.h"
#include "GuiTransition.h"

#include "../utils/LinkedList.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class GuiComponent
      {
      protected:
        bool isHovered;
      public:
        float x;
        float y;

        float width;
        float height;

        LinkedList<GuiTransition*> transitions;

        GuiComponent();
        GuiComponent(const GuiComponent&);
        GuiComponent& operator=(const GuiComponent&);
        virtual ~GuiComponent();

        virtual void updateMouseData(bool, float, float, float, float);
        virtual void update(float);
        virtual void onLeftClick();
        virtual void render(GuiRenderer*, float, float);

        void setTransition(GuiTransition*);
      };
    }
  }
}

#endif
