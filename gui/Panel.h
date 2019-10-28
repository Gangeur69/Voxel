#ifndef PANEL_H
#define PANEL_H

#include "GuiRenderer.h"
#include "GuiComponent.h"
#include "../utils/LinkedList.h"
#include "text/Text.h"

using namespace gt::doubovik::utils;
using namespace gt::doubovik::gui::text;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class Panel : public GuiComponent
      {
      private:
        Text* title;

        void renderTitle(GuiRenderer*, float, float);
      public:
        bool isVisible;
        LinkedList<GuiComponent*> components;

        Panel();
        Panel(const Panel&);
        Panel& operator=(const Panel&);
        virtual ~Panel();

        virtual void render(GuiRenderer*, float, float);
        virtual void updateMouseData(bool, float, float, float, float);
        virtual void update(float timePassed);

        void addComponent(GuiComponent*);
        void setTitle(Text*);
        void clearComponents();
      };
    }
  }
}

#endif
