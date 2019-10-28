#ifndef GUITRANSLATIONTRANSITION
#define GUITRANSLATIONTRANSITION

#include "../GuiTransition.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      namespace transitions
      {
        class GuiTranslationTransition : public GuiTransition
        {
        private:
          float startx;
          float starty;

          float endx;
          float endy;
        public:
          GuiTranslationTransition(float, float, float, float, float);
          GuiTranslationTransition(const GuiTranslationTransition&);
          GuiTranslationTransition& operator=(const GuiTranslationTransition&);

          virtual float getX();
          virtual float getY();
        };
      }
    }
  }
}

#endif
