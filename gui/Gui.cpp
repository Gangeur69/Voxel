#include "Gui.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      Gui::Gui()
      {
      }

      Gui::Gui(const Gui& gui)
      {
        components = gui.components;
      }

      Gui& Gui::operator=(const Gui& gui)
      {
        components = gui.components;
        return *this;
      }

      void Gui::addComponent(GuiComponent* component)
      {
        components.add(component);
      }

      void Gui::render(GuiRenderer* renderer)
      {
        for(LinkedListIterator<GuiComponent*> itt=components.getIterator();itt.isValid();itt.next())
        {
          itt.getElement()->render(renderer, 0.0,0.0);
        }
      }

      void Gui::updateMouseData(bool leftClick, float mx, float my)
      {
        for(LinkedListIterator<GuiComponent*> itt=components.getIterator();itt.isValid();itt.next())
        {
          itt.getElement()->updateMouseData(leftClick, 0.0, 0.0, mx, my);
        }
      }

      void Gui::update(float timePassed)
      {
        for(LinkedListIterator<GuiComponent*> itt=components.getIterator();itt.isValid();itt.next())
        {
          itt.getElement()->update(timePassed);
        }
      }
    }
  }
}
