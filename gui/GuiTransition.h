#ifndef GUITRANSITION_H
#define GUITRANSITION_H

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class GuiTransition
      {
      protected:
        float duration;
        float currentTime;
        bool finished;

      public:
        GuiTransition(float);
        GuiTransition(const GuiTransition&);
        GuiTransition& operator=(const GuiTransition&);

        virtual void update(float);
        virtual float getX();
        virtual float getY();

        bool isFinished() const;
      };
    }
  }
}

#endif
