#include "GuiComponent.h"

#include "../math/geometry/Rectangle.h"
#include <iostream>

using namespace gt::doubovik::math::geometry;

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      GuiComponent::GuiComponent()
      {
        x = 0.0;
        y = 0.0;
        isHovered = false;
      }

      GuiComponent::GuiComponent(const GuiComponent& component)
      {
        x = component.x;
        y = component.y;
        width = component.width;
        height = component.height;
      }

      GuiComponent& GuiComponent::operator=(const GuiComponent& component)
      {
        x = component.x;
        y = component.y;
        width = component.width;
        height = component.height;
        return *this;
      }

      GuiComponent::~GuiComponent()
      {
        for(LinkedListIterator<GuiTransition*> itt=transitions.getIterator();itt.isValid();itt.next())
        {
          delete itt.getElement();
        }
      }

      void GuiComponent::updateMouseData(bool leftClick, float parentx, float parenty, float mx, float my)
      {
        Rectangle rectangle(parentx + x, parenty + y, width, height);
        if(rectangle.isInside(mx, my))
        {
          isHovered = true;
          if(leftClick)
          {
            onLeftClick();
          }
        }
        else
        {
          isHovered = false;
        }
      }

      void GuiComponent::update(float timePassed)
      {
        if(!transitions.isEmpty())
        {
          GuiTransition* transition = transitions.getFirst();
          transition->update(timePassed);
          x = transition->getX();
          y = transition->getY();
          if(transition->isFinished())
          {
            delete transition;
            transitions.removeFirst();
          }
        }
      }

      void GuiComponent::onLeftClick()
      {

      }

      void GuiComponent::render(GuiRenderer*, float, float)
      {

      }

      void GuiComponent::setTransition(GuiTransition* transition)
      {
        transitions.clear();
        transitions.add(transition);
      }
    }
  }
}
