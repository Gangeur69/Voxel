#include "GuiTransition.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      GuiTransition::GuiTransition(float duration)
      {
        this->duration = duration;
        currentTime = 0.0;
        finished = false;
      }

      GuiTransition::GuiTransition(const GuiTransition& transition)
      {
        duration = transition.duration;
        currentTime = transition.currentTime;
        finished = transition.finished;
      }

      GuiTransition& GuiTransition::operator=(const GuiTransition& transition)
      {
        duration = transition.duration;
        currentTime = transition.currentTime;
        finished = transition.finished;
        return *this;
      }

      void GuiTransition::update(float timePassed)
      {
        currentTime+=timePassed;
        if(currentTime >= duration)
        {
          finished = true;
          currentTime = duration;
        }
      }

      float GuiTransition::getX()
      {
        return 0.0;
      }

      float GuiTransition::getY()
      {
        return 0.0;
      }

      bool GuiTransition::isFinished() const
      {
        return finished;
      }
    }
  }
}
