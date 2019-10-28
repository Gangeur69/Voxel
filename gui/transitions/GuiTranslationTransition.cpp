#include "GuiTranslationTransition.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace transitions
      {
        GuiTranslationTransition::GuiTranslationTransition(float duration, float startx, float starty, float endx, float endy) : GuiTransition(duration)
        {
          this->startx = startx;
          this->starty = starty;

          this->endx = endx;
          this->endy = endy;
        }

        GuiTranslationTransition::GuiTranslationTransition(const GuiTranslationTransition& transition) : GuiTransition(transition)
        {
          startx = transition.startx;
          starty = transition.starty;

          endx = transition.endx;
          endy = transition.endy;
        }

        GuiTranslationTransition& GuiTranslationTransition::operator=(const GuiTranslationTransition& transition)
        {
          GuiTransition::operator=(transition);
          startx = transition.startx;
          starty = transition.starty;

          endx = transition.endx;
          endy = transition.endy;
          return *this;
        }

        float GuiTranslationTransition::getX()
        {
          return startx + (endx - startx)*(currentTime/duration);
        }

        float GuiTranslationTransition::getY()
        {
          return starty + (endy - starty)*(currentTime/duration);
        }
      }
    }
  }
}
