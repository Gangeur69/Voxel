#ifndef GUI_H
#define GUI_H

#include "GuiComponent.h"
#include "GuiRenderer.h"
#include "../utils/LinkedList.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class Gui
      {
      private:
        LinkedList<GuiComponent*> components;

      public:
        Gui();
        Gui(const Gui&);
        Gui& operator=(const Gui&);

        void addComponent(GuiComponent*);
        void render(GuiRenderer*);
        void updateMouseData(bool, float, float);
        void update(float timePassed);
      };
    }
  }
}

#endif
