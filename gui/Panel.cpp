#include "Panel.h"

#include "../math/Vector3.h"

using namespace gt::doubovik::math;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      Panel::Panel() : GuiComponent()
      {
        x = 0.0;
        y = 0.0;
        width = 0.5; //0.2 + 0.12 = 0.32
        height = 0.5;
        isVisible = true;

        title = NULL;
      }

      Panel::Panel(const Panel& panel) : GuiComponent(panel)
      {
        x = panel.x;
        y = panel.y;
        width = panel.width;
        height = panel.height;
        isVisible = panel.isVisible;
        title = panel.title;
      }

      Panel& Panel::operator=(const Panel& panel)
      {
        GuiComponent::operator=(panel);
        x = panel.x;
        y = panel.y;
        width = panel.width;
        height = panel.height;
        isVisible = panel.isVisible;
        title = panel.title;
        return *this;
      }

      Panel::~Panel()
      {

      }

      void Panel::renderTitle(GuiRenderer* renderer, float parentx, float parenty)
      {
        if(title != NULL)
        {
          float tx = parentx + x + (width/2.0) - (title->getWidth()/2.0);
          float ty = parenty + y + 0.02;
          renderer->renderPanel(0.06, tx, ty, title->getWidth(), title->getHeight(), Vector3(1.0,1.0,1.0));
          renderer->renderText(tx, ty, *title);
        }
      }

      void Panel::render(GuiRenderer* renderer, float parentx, float parenty)
      {
        if(!isVisible)
        {
          return;
        }
        GuiComponent::render(renderer, parentx, parenty);
        renderer->renderPanel(0.06, parentx + x, parenty + y, width, height, Vector3(1.0,1.0,1.0));

        for(LinkedListIterator<GuiComponent*> itt=components.getIterator(); itt.isValid(); itt.next())
        {
          itt.getElement()->render(renderer, parentx + x, parenty + y);
        }
        renderTitle(renderer, parentx, parenty);
      }

      void Panel::updateMouseData(bool leftClick, float parentx, float parenty, float mx, float my)
      {
        if(!isVisible)
        {
          return;
        }
        GuiComponent::updateMouseData(leftClick, parentx, parenty, mx, my);
        for(LinkedListIterator<GuiComponent*> itt=components.getIterator(); itt.isValid(); itt.next())
        {
          itt.getElement()->updateMouseData(leftClick, parentx + x, parenty + y, mx, my);
        }
      }

      void Panel::update(float timePassed)
      {
        if(!isVisible)
        {
          return;
        }
        GuiComponent::update(timePassed);
        for(LinkedListIterator<GuiComponent*> itt=components.getIterator(); itt.isValid(); itt.next())
        {
          itt.getElement()->update(timePassed);
        }
      }

      void Panel::addComponent(GuiComponent* component)
      {
        components.add(component);
      }

      void Panel::setTitle(Text* title)
      {
        this->title = title;
      }

      void Panel::clearComponents()
      {
        components.clear();
      }
    }
  }
}
