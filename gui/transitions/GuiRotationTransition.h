#ifndef GUIROTATIONTRANSITION_H
#define GUIROTATIONTRANSITION_H

#include "../GuiTransition.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace transitions
      {
        class GuiRotationTransition : public GuiTransition
        {
        private:
          float x;
          float y;

          float radius;
          float startAngle;
          float endAngle;
        public:
          GuiRotationTransition(float, float, float, float, float, float);
          GuiRotationTransition(const GuiRotationTransition&);
          GuiRotationTransition& operator=(const GuiRotationTransition&);

          virtual float getX();
          virtual float getY();
        };
      }
    }
  }
}

#endif
