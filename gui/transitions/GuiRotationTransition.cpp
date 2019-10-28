#include "GuiRotationTransition.h"

#include <cmath>

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace transitions
      {
        GuiRotationTransition::GuiRotationTransition(float duration, float x, float y, float radius, float startAngle, float endAngle) : GuiTransition(duration)
        {
          this->x = x;
          this->y = y;

          this->radius = radius;
          this->startAngle = startAngle;
          this->endAngle = endAngle;
        }

        GuiRotationTransition::GuiRotationTransition(const GuiRotationTransition& transition) : GuiTransition(transition)
        {
          x = transition.x;
          y = transition.y;

          radius = transition.radius;
          startAngle = transition.startAngle;
          endAngle = transition.endAngle;
        }
        GuiRotationTransition& GuiRotationTransition::operator=(const GuiRotationTransition& transition)
        {
          GuiTransition::operator=(transition);
          x = transition.x;
          y = transition.y;

          radius = transition.radius;
          startAngle = transition.startAngle;
          endAngle = transition.endAngle;
          return *this;
        }

        float GuiRotationTransition::getX()
        {
          float angle = startAngle + (currentTime/duration) * (endAngle - startAngle);
          angle = (M_PI/180.0)*angle;
          return x + radius*cos(angle);
        }

        float GuiRotationTransition::getY()
        {
          float angle = startAngle + (currentTime/duration) * (endAngle - startAngle);
          angle = (M_PI/180.0)*angle;
          return y + radius*sin(angle);
        }
      }
    }
  }
}
